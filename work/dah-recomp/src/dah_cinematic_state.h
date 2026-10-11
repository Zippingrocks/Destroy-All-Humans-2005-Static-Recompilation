#ifndef DAH_CINEMATIC_STATE_H
#define DAH_CINEMATIC_STATE_H
/* Include after dah_parity_farm_range/word/scalar. Read-only in-engine movie
 * diagnostics, independent of Bink playback. Retail sources: 00112D80 manager
 * and derived vtable override 0005CD65,
 * 00112BE0 list update, 00112280 movie/0005910E derived override,
 * 00111EE0 start, 00111CE0 elapsed,
 * 00111F90 finish. All floats remain raw bits, including pre-ready storage. */
typedef struct {
    uint32_t node,object,vtable,name_hash,duration_bits,elapsed_bits,flags,state;
    int header_valid,fields_valid,complete;
} DahCinematicEntry;
typedef struct {
    uint32_t manager,manager_vtable,declared_count;
    unsigned reads,bytes,count;
    int pointer_valid,header_valid,list_valid,complete;
    const char *reason;
    DahCinematicEntry entries[16];
} DahCinematicState;
static void dah_cinematic_fail(DahCinematicState *s,const char *reason)
{ if(!s->reason)s->reason=reason; }
static int dah_cinematic_block(DahCinematicState *s,uint32_t a,unsigned n)
{
    if(!n||(a&3u)||!((a>=0x10000u&&a<0x08000000u&&n<=0x08000000u-a)||
        (a>=0x80000000u&&a<0x88000000u&&n<=0x88000000u-a))){
        dah_cinematic_fail(s,"invalid guest RAM address");return 0;
    }
    if(s->reads+1u>34u||s->bytes+n>2144u){
        dah_cinematic_fail(s,"cinematic read budget exceeded");return 0;
    }
    ++s->reads;s->bytes+=n;
    if(!dah_parity_farm_range(a,n)){dah_cinematic_fail(s,"guest memory unavailable");return 0;}
    return 1;
}
static DahCinematicState dah_cinematic_read(void)
{
    DahCinematicState s={0};uint32_t seen[16],objects[16];unsigned visited=0,object_count=0;
    if(!dah_cinematic_block(&s,0x286784u,4))return s;
    s.pointer_valid=1;s.manager=dah_parity_farm_word(0x286784u);
    if(!s.manager){s.list_valid=1;s.complete=1;return s;}
    if(!dah_cinematic_block(&s,s.manager,0x1cu))return s;
    s.header_valid=1;s.manager_vtable=dah_parity_farm_word(s.manager);
    if(s.manager_vtable!=0x23611cu&&s.manager_vtable!=0x22a6b8u){dah_cinematic_fail(&s,"unexpected cinematic manager vtable");return s;}
    s.declared_count=dah_parity_farm_word(s.manager+0x18u);s.list_valid=1;
    uint32_t sentinel=s.manager+8u,tail=dah_parity_farm_word(s.manager+12u);
    uint32_t node=dah_parity_farm_word(s.manager+8u),previous=sentinel;
    while(node!=sentinel){
        int duplicate=0;
        if(!node){dah_cinematic_fail(&s,"null cinematic list link");break;}
        for(unsigned i=0;i<visited;++i)if(seen[i]==node)duplicate=1;
        if(duplicate){dah_cinematic_fail(&s,"cyclic cinematic list");break;}
        if(visited==16u){dah_cinematic_fail(&s,"cinematic list exceeds 16 entries");break;}
        seen[visited++]=node;
        if(!dah_cinematic_block(&s,node,12))break;
        if(dah_parity_farm_word(node+4u)!=previous){dah_cinematic_fail(&s,"cinematic previous-link mismatch");break;}
        DahCinematicEntry *e=&s.entries[s.count++];e->node=node;e->object=dah_parity_farm_word(node+8u);
        for(unsigned i=0;i<object_count;++i)if(objects[i]==e->object)duplicate=1;
        if(duplicate){dah_cinematic_fail(&s,"duplicate cinematic object");break;}
        objects[object_count++]=e->object;
        if(dah_cinematic_block(&s,e->object,0x78u)){
            e->header_valid=1;e->vtable=dah_parity_farm_word(e->object);
            if(e->vtable!=0x236100u&&e->vtable!=0x229fb4u)dah_cinematic_fail(&s,"unexpected cinematic movie vtable");
            else{
                e->fields_valid=1;e->name_hash=dah_parity_farm_word(e->object+0x20u);
                e->duration_bits=dah_parity_farm_word(e->object+0x68u);
                e->elapsed_bits=dah_parity_farm_word(e->object+0x6cu);
                e->flags=dah_parity_farm_word(e->object+0x70u);e->state=dah_parity_farm_word(e->object+0x74u);
                e->complete=e->state<=3u;if(!e->complete)dah_cinematic_fail(&s,"invalid cinematic movie state");
            }
        }
        previous=node;node=dah_parity_farm_word(node);
    }
    if(node==sentinel&&tail!=previous)dah_cinematic_fail(&s,"cinematic tail-link mismatch");
    if(s.count!=s.declared_count)dah_cinematic_fail(&s,"cinematic count mismatch");
    s.complete=s.reason==NULL;return s;
}
static void dah_parity_write_cinematic(FILE *output)
{
    DahCinematicState s=dah_cinematic_read();
    dah_parity_farm_scalar(output,"cinematicManager",s.pointer_valid,s.manager);
    dah_parity_farm_scalar(output,"cinematicManagerVtable",s.header_valid,s.manager_vtable);
    dah_parity_farm_scalar(output,"cinematicDeclaredCount",s.header_valid&&s.list_valid,s.declared_count);
    fputs(",\"cinematics\":",output);
    if(!s.list_valid)fputs("null",output);
    else{
        fputc('[',output);
        for(unsigned i=0;i<s.count;++i){
            DahCinematicEntry *e=&s.entries[i];
            fprintf(output,"%s{\"node\":%u,\"object\":%u",i?",":"",e->node,e->object);
            dah_parity_farm_scalar(output,"vtable",e->header_valid,e->vtable);
            dah_parity_farm_scalar(output,"nameHash",e->fields_valid,e->name_hash);
            dah_parity_farm_scalar(output,"durationBits",e->fields_valid,e->duration_bits);
            dah_parity_farm_scalar(output,"elapsedBits",e->fields_valid,e->elapsed_bits);
            dah_parity_farm_scalar(output,"flags",e->fields_valid,e->flags);
            dah_parity_farm_scalar(output,"state",e->fields_valid,e->state);
            fprintf(output,",\"complete\":%s}",e->complete?"true":"false");
        }
        fputc(']',output);
    }
    fprintf(output,",\"cinematicComplete\":%s,\"cinematicReason\":",s.complete?"true":"false");
    if(s.reason)fprintf(output,"\"%s\"",s.reason);else fputs("null",output);
    fprintf(output,",\"cinematicMemoryReads\":%u,\"cinematicMemoryBytes\":%u",s.reads,s.bytes);
}
#endif
