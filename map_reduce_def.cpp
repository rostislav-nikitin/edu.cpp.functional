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
	FaceImage result = empty_face_image;
	for(const Image &image : images)
	{
		FaceImage face_image = extract_face(image);
		result = add_face_image(result, face_image);
	}

	result = divide_values(result, images.size());

	return result;
}


int main()
{
	Images images =
	{
		Image{1}, Image{2}, Image{3}, Image{4}, Image{5}
	};

	FaceImage result = create(images);

	cout << result.get_id() << endl;

	//FaceImage fi {1};

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
