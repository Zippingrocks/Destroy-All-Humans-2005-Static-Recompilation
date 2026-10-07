# Ion Detonator first-appearance crash — retail repair

The October 7 crash first exposed four unresolved indirect calls at retail
addresses `0x00075660`, `0x00075800`, `0x00075780`, and `0x00075A10`. The
later null call at `0x00198855` occurred only after those object methods had
been skipped, so the repair restores the missing retail behavior rather than
masking the final invalid call.

All four addresses are stored in the retail table rooted at `0x0022C1AC`.
Their exact function boundaries are established by retail instruction flow,
the terminating `ret`, and the following `0xCC` padding. The deterministic
lift records both each byte-range hash and its retail table slot in
`tools/analysis/results/ion-detonator-retail-callback-evidence.json`.

No alpha executable, PDB, or inferred source-level name is used by this
repair. The functions retain their retail address names until retail evidence
supports stronger semantics.
