#include <iostream>
#include <fplus/fplus.hpp>

using namespace std;
using namespace fplus;

struct Image
{
	int id;
	Image(int id) : id{id} {}
	int get_id() const
	{
		return id;
	}
};

struct FaceImage
{
	int id;
	FaceImage() = default;
	FaceImage(int id) : id{id} {}
	FaceImage(const Image &i)
	{
		id = i.id;
	}
	FaceImage(Image &&i)
	{
		id = i.id;
	}
	int get_id() const
	{
		return id;
	}
	
};

typedef vector<Image> Images;

FaceImage extract_face(const Image &i);
FaceImage add_face_image(const FaceImage &fi1, const FaceImage &fi2);
FaceImage divide_values(const FaceImage &fi, const int size);

const FaceImage empty_face_image {0};

FaceImage create(const Images &images)
{
	auto result = fplus::transform_reduce_parallelly
	(
		 extract_face, 
		 add_face_image, 
		 empty_face_image, 
		 images
	);

	result = divide_values(result, images.size());

	return result;
}


int main()
{
	const int IMG_COUNT = 100000000;

	Images images {};
	images.reserve(IMG_COUNT);

	for(int i = 0; i < IMG_COUNT; ++i)
	{
		images.push_back(Image{i});
	}

	cout << "Images was created" << endl;

	FaceImage result = create(images);

	cout << result.get_id() << endl;

	return 0;
}

FaceImage extract_face(const Image &i)
{
	return FaceImage(i);
}

FaceImage add_face_image(const FaceImage &fi1, const FaceImage &fi2)
{
	return FaceImage{fi1.get_id() + fi2.get_id()};
}

FaceImage divide_values(const FaceImage &fi, const int size)
{
	return FaceImage{fi.get_id() / size};
}
