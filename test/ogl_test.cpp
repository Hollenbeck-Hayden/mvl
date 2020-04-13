#include <iostream>
#include <iomanip>

#include "../src/mvl.h"
#include "../src/affine.h"

template<typename T, size_t N>
void print_vector(const mvl::Vector<T,N>& v)
{
	std::cout << "[";
	for (size_t i = 0; i < N-1; i++)
		std::cout << v[i] << ", ";
	std::cout << v[N-1] << "]" << std::endl;
}

int main( void )
{
	std::cout << std::showpoint << std::showpos << std::setprecision(3) << std::fixed;

	mvl::Vector<float,4> box_center;
	box_center[0] = 2;
	box_center[1] = -3;
	box_center[2] = 5;
	box_center[3] = 1;

	float box_size = 0.5;
//	auto box_axis1 = aff::x_axis<float,4>();
//	auto box_axis2 = aff::y_axis<float,4>();

	mvl::Vector<float,4> box_axis1, box_axis2;
	box_axis1[0] =  0;	box_axis2[0] =  0;
	box_axis1[1] =  1;	box_axis2[1] = -1;
	box_axis1[2] =  1;	box_axis2[2] =  1;
	box_axis1[3] =  0;	box_axis2[3] =  0;

	normalize(box_axis1);
	normalize(box_axis2);

	auto box_r = box_center + box_size * box_axis1;
	auto box_l = box_center - box_size * box_axis1;
	auto box_t = box_center + box_size * box_axis2;
	auto box_b = box_center - box_size * box_axis2;
	auto box_rt = box_center + box_size * ( box_axis1 + box_axis2);
	auto box_lt = box_center + box_size * (-box_axis1 + box_axis2);
	auto box_rb = box_center + box_size * ( box_axis1 - box_axis2);
	auto box_lb = box_center + box_size * (-box_axis1 - box_axis2);


	mvl::Vector<float,3> box_axis1_3, box_axis2_3;
	for (size_t i = 0; i < 3; i++)
	{
		box_axis1_3[i] = box_axis1[i];
		box_axis2_3[i] = box_axis2[i];
	}

	auto normal_vector = mvl::cross(box_axis1_3, box_axis2_3);
	std::cout << "Normal vector: "; print_vector(normal_vector);

	mvl::Vector<float,3> box_center3;
	for (size_t i = 0; i < 3; i++)
		box_center3[i] = box_center[i];
	
	auto camera_pos = box_center3 - normal_vector;
	mvl::Vector<float,3> up = box_axis2_3;

	auto view_matrix = aff::lookAt(camera_pos, box_center3, up);

	mvl::Vector<float,3> dims;
	dims[0] = box_size * 4;
	dims[1] = box_size * 4;
	dims[2] = norm(camera_pos - box_center3) * 2;
	auto proj_matrix = aff::orthographic_box(mvl::Vector<float,3>(), dims);

	std::cout << "Box coordinates:" << std::endl;
	std::cout << "Top right: "; print_vector(box_rt);
	std::cout << "Top left:  "; print_vector(box_lt);
	std::cout << "Bot right: "; print_vector(box_rb);
	std::cout << "Bot left:  "; print_vector(box_lb);


	auto camera_rt = view_matrix * box_rt;
	auto camera_lt = view_matrix * box_lt;
	auto camera_rb = view_matrix * box_rb;
	auto camera_lb = view_matrix * box_lb;

	std::cout << std::endl << "Translate Matrix: " << std::endl;
	for (size_t i = 0; i < 4; i++)
		print_vector(mvl::transpose(aff::translate(box_center3-normal_vector).getRow(i)));

	std::cout << std::endl << "View Matrix: " << std::endl;
	for (size_t i = 0; i < 4; i++)
		print_vector(mvl::transpose(view_matrix.getRow(i)));

	std::cout << std::endl << "Camera coordinates:" << std::endl;
	std::cout << "Top right: "; print_vector(camera_rt);
	std::cout << "Top left:  "; print_vector(camera_lt);
	std::cout << "Bot right: "; print_vector(camera_rb);
	std::cout << "Bot left:  "; print_vector(camera_lb);


	auto screen_rt = proj_matrix * camera_rt;
	auto screen_lt = proj_matrix * camera_lt;
	auto screen_rb = proj_matrix * camera_rb;
	auto screen_lb = proj_matrix * camera_lb;

	std::cout << std::endl << "Proj Matrix: " << std::endl;
	for (size_t i = 0; i < 4; i++)
		print_vector(mvl::transpose(proj_matrix.getRow(i)));

	std::cout << std::endl << "Screen coordinates:" << std::endl;
	std::cout << "Top right: "; print_vector(screen_rt);
	std::cout << "Top left:  "; print_vector(screen_lt);
	std::cout << "Bot right: "; print_vector(screen_rb);
	std::cout << "Bot left:  "; print_vector(screen_lb);

	return 0;
}
