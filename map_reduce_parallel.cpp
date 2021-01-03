#include <fplus/fplus.hpp>

struct Image {}; // dummy
struct FaceImage { int dummy;  }; // dummy
std::vector<Image> images;
FaceImage extract_face(Image) { return {}; } // dummy
FaceImage empty_face_image; // dummy
FaceImage add_face_images(FaceImage, FaceImage) { return {}; } // dummy
FaceImage divide_values(FaceImage, std::size_t) { return {}; } // dummy
const int IMG_COUNT = 1000000;

int main()
{
    images.reserve(IMG_COUNT);
    for(int i = 0; i < IMG_COUNT; ++i)
        images.push_back(Image{});
    std::cout << "Images was created" << std::endl;
  
    FaceImage result = fplus::transform_reduce_parallelly(
        extract_face, add_face_images, empty_face_image, images);
    std::cout << result.dummy << std::endl;
}
