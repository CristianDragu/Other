#include <stdio.h>
#include <CL/cl.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "helper.hpp"

using namespace std;

#define max_length 50001
#define buffer_size 1000

FILE *f;

cl_float *latitudine;
cl_float *longitudine;
cl_int *population;

cl_int length = 0;
cl_int kmrange = 0;

/**
* Retrieve GPU device
*/
void gpu_find(cl_device_id &device)
{
	cl_platform_id platform;
	cl_uint platform_num = 0;
	cl_platform_id* platform_list = NULL;

	cl_uint device_num = 0;
	cl_device_id* device_list = NULL;

	size_t attr_size = 0;
	cl_char* attr_data = NULL;

	/* get num of available OpenCL platforms */
	CL_ERR( clGetPlatformIDs(0, NULL, &platform_num));
	platform_list = new cl_platform_id[platform_num];
	DIE(platform_list == NULL, "alloc platform_list");

	/* get all available OpenCL platforms */
	CL_ERR( clGetPlatformIDs(platform_num, platform_list, NULL));

	/* list all platforms and VENDOR/VERSION properties */
	for(uint i=0; i<platform_num; i++)
	{
		/* get attribute CL_PLATFORM_VENDOR */
		CL_ERR( clGetPlatformInfo(platform_list[i],
				CL_PLATFORM_VENDOR, 0, NULL, &attr_size));
		attr_data = new cl_char[attr_size];
		DIE(attr_data == NULL, "alloc attr_data");

		/* get data CL_PLATFORM_VENDOR */
		CL_ERR( clGetPlatformInfo(platform_list[i],
				CL_PLATFORM_VENDOR, attr_size, attr_data, NULL));

		/* select platform based on CL_PLATFORM_VENDOR */
		if(string((const char*)attr_data).find("NVIDIA", 0) != string::npos)
			platform = platform_list[i]; /* select NVIDIA platform */
		delete[] attr_data;

		/* get attribute size CL_PLATFORM_VERSION */
		CL_ERR( clGetPlatformInfo(platform_list[i],
				CL_PLATFORM_VERSION, 0, NULL, &attr_size));
		attr_data = new cl_char[attr_size];
		DIE(attr_data == NULL, "alloc attr_data");

		/* get data size CL_PLATFORM_VERSION */
		CL_ERR( clGetPlatformInfo(platform_list[i],
				CL_PLATFORM_VERSION, attr_size, attr_data, NULL));
		delete[] attr_data;
	}

	/* no platform found */
	DIE(platform == 0, "platform selection");

	/* get num of available OpenCL devices type GPU on the selected platform */
	CL_ERR( clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &device_num));
	device_list = new cl_device_id[device_num];
	DIE(device_list == NULL, "alloc devices");

	/* get all available OpenCL devices type GPU on the selected platform */
	CL_ERR( clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU,
		  device_num, device_list, NULL));

	/* list all devices and TYPE/VERSION properties */
	for(uint i=0; i<device_num; i++)
	{
		/* get attribute size */
		CL_ERR( clGetDeviceInfo(device_list[i], CL_DEVICE_NAME,
				0, NULL, &attr_size));
		attr_data = new cl_char[attr_size];
		DIE(attr_data == NULL, "alloc attr_data");

		/* get attribute CL_DEVICE_NAME */
		CL_ERR( clGetDeviceInfo(device_list[i], CL_DEVICE_NAME,
				attr_size, attr_data, NULL));

		delete[] attr_data;

		/* get attribute size */
		CL_ERR( clGetDeviceInfo(device_list[i], CL_DEVICE_VERSION,
				0, NULL, &attr_size));
		attr_data = new cl_char[attr_size];
		DIE(attr_data == NULL, "alloc attr_data");

		/* get attribute CL_DEVICE_VERSION */
		CL_ERR( clGetDeviceInfo(device_list[i], CL_DEVICE_VERSION,
				attr_size, attr_data, NULL));
		delete[] attr_data;
	}

	/* select first available GPU */
	if(device_num > 0)
		device = device_list[0];
	else
		device = 0;

	delete[] platform_list;
	delete[] device_list;
}

/**
* Exec kernel using the select device
*/
void gpu_execute_kernel(cl_device_id device)
{
	cl_int ret;

	cl_context context;
	cl_command_queue cmd_queue;
	cl_program program;
	cl_kernel kernel;

	string kernel_src;

	/* create a context for the device */
	context = clCreateContext(0, 1, &device, NULL, NULL, &ret);
	CL_ERR( ret );

	/* create a command queue for the device in the context */
	cmd_queue = clCreateCommandQueue(context, device, 0, &ret);
	CL_ERR( ret );

	//allocate buffers on GPU
	cl_mem device_latitudine = clCreateBuffer(context, CL_MEM_READ_WRITE, length * sizeof(cl_float), NULL, &ret);
	cl_mem device_longitudine = clCreateBuffer(context, CL_MEM_READ_WRITE, length * sizeof(cl_float), NULL, &ret);
	cl_mem device_population = clCreateBuffer(context, CL_MEM_READ_WRITE, length * sizeof(cl_int), NULL, &ret);
	cl_mem outputs = clCreateBuffer(context, CL_MEM_READ_WRITE, length * sizeof(cl_int), NULL, &ret);
	cl_int *output = new cl_int[length];

	//copy vectors to GPU
	clEnqueueWriteBuffer(cmd_queue, device_latitudine, CL_TRUE, 0, length * sizeof(cl_float), latitudine, 0, NULL, NULL);
	clEnqueueWriteBuffer(cmd_queue, device_longitudine, CL_TRUE, 0, length * sizeof(cl_float), longitudine, 0, NULL, NULL);
	clEnqueueWriteBuffer(cmd_queue, device_population, CL_TRUE, 0, length * sizeof(cl_int), population, 0, NULL, NULL);
	clEnqueueWriteBuffer(cmd_queue, outputs, CL_TRUE, 0, length * sizeof(cl_int), population, 0, NULL, NULL);

	/* retrieve kernel source */
	read_kernel("device.cl", kernel_src);
	const char* kernel_c_str = kernel_src.c_str();

	/* create kernel program from source */
	program = clCreateProgramWithSource(context, 1,
		  &kernel_c_str, NULL, &ret);
	CL_ERR( ret );

	/* compile the program for the given set of devices */
	ret = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	CL_COMPILE_ERR( ret, program, device );

	/* create kernel associated to compiled source kernel */
	kernel = clCreateKernel(program, "kernel_id", &ret);
	CL_ERR( ret );

	/* set OpenCL kernel argument */
	CL_ERR( clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&device_latitudine) );
	CL_ERR( clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&device_longitudine) );
	CL_ERR( clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&device_population) );
	CL_ERR( clSetKernelArg(kernel, 3, sizeof(cl_int), &kmrange) );
	CL_ERR( clSetKernelArg(kernel, 4, sizeof(cl_int), &length) );
	CL_ERR( clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&outputs) );

	/* Execute OpenCL kernel */
	size_t globalSize[2] = {length, 0};

	ret = clEnqueueNDRangeKernel(cmd_queue, kernel, 1, NULL,
		  globalSize, NULL, 0, NULL, NULL);
	CL_ERR( ret );

	/* copy the output buffer back */
	CL_ERR( clEnqueueReadBuffer(cmd_queue, outputs, CL_TRUE, 0,
		  sizeof(cl_int) * length, output, 0, NULL, NULL));

	for(int i = 0; i < length; i++)
		cout << output[i] << "\n";

	/* wait for all enqueued operations to finish */
	CL_ERR( clFinish(cmd_queue) );

	/* free all resources related to GPU */
	CL_ERR( clReleaseMemObject(device_latitudine) );
	CL_ERR( clReleaseMemObject(device_longitudine) );
	CL_ERR( clReleaseMemObject(device_population) );
	CL_ERR( clReleaseMemObject(outputs) );
	CL_ERR( clReleaseCommandQueue(cmd_queue) );
	CL_ERR( clReleaseContext(context) );

	/* free all resources on CPU */
	delete[] output;
	delete[] latitudine;
	delete[] longitudine;
	delete[] population;
}

/*
	Reads data from the input file and stores it into vectors
*/
void init_data()
{
	char asciiname[buffer_size], country_code[buffer_size];
	int geonameid;
	int ret;

	latitudine = (cl_float*)malloc(max_length * sizeof(cl_float));
	longitudine = (cl_float*)malloc(max_length * sizeof(cl_float));
	population = (cl_int*)malloc(max_length * sizeof(cl_int));

	char *buf = (char*)malloc(buffer_size * sizeof(char));

	//ignore the first line in the input file
	fgets(asciiname, buffer_size, f);

	length = 0;

	//read each line until the end of the file is reached
	while(fgets(buf, buffer_size, f) != NULL) {
			//copy data into vectors
			sscanf(buf, "%d %s %f,%f %s %d\n", &geonameid, asciiname, 
				&latitudine[length], &longitudine[length], 
				country_code, &population[length]);			
			length++;
		}
}

int main(int argc, char** argv)
{
	cl_device_id device;

	kmrange = atoi(argv[1]);

	f = fopen(argv[2], "r");

	init_data();

	gpu_find(device);
	DIE(device == 0, "check valid device");

	gpu_execute_kernel(device);

	return 0;
}
