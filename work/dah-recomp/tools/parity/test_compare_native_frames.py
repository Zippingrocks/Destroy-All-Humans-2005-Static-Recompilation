import unittest
from PIL import Image
from compare_native_frames import compare


class ExactFrameTests(unittest.TestCase):
    def test_identical_pixels_do_not_prove_timing(self):
        result, _ = compare(Image.new('RGB', (2, 2)), Image.new('RGB', (2, 2)))
        self.assertTrue(result['exactPixels'])
        self.assertFalse(result['timingVerified'])

    def test_single_channel_single_level_difference_fails(self):
        right = Image.new('RGB', (2, 2))
        right.putpixel((1, 0), (1, 0, 0))
        result, diff = compare(Image.new('RGB', (2, 2)), right)
        self.assertFalse(result['exactPixels'])
        self.assertEqual(result['differentPixels'], 1)
        self.assertEqual(result['differenceBounds'], [1, 0, 2, 1])
        self.assertEqual(diff.getpixel((1, 0)), (1, 0, 0))

    def test_dimensions_are_never_rescaled(self):
        result, diff = compare(Image.new('RGB', (2, 2)), Image.new('RGB', (4, 4)))
        self.assertFalse(result['sameDimensions'])
        self.assertFalse(result['exactPixels'])
        self.assertIsNone(diff)


if __name__ == '__main__':
    unittest.main()
