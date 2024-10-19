#include <stddef.h>
#include <stdio.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALOC malloc
#endif //NN_MALOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif

#define MAT_AT(m, i, j) (m).es[(i)*(m).cols + (j)] //This is a macro that takes the memory addres and manipullates to get the element by iteration i and j

float rand_float(void);

#ifndef NN_H_
#define NN_H_

typedef struct {
	size_t rows;
	size_t cols;
	float* es;
} Mat;

Mat mat_alloc(size_t rows, size_t cols);
void mat_dot(Mat dest, Mat a, Mat b);
void mat_sum(Mat dest, Mat a, Mat b);
void mat_print(Mat m);
void mat_rand(Mat m, float low, float high);

#endif //NN_H_

#ifndef NN_IMPLEMENTATION

float rand_float(void) {
	(float)rand() / (float)RAND_MAX; //Random number from 0 to 1
}

Mat mat_alloc(size_t rows, size_t cols) {
	Mat m;
	m.rows = rows;
	m.cols = cols;
	m.es = NN_malloc(sizeof(*m.es));
	NN_assert(m.es != NULL);
	return m;

};
void mat_dot(Mat dest, Mat a, Mat b) {
	(void) dest;
	(void) a;
	(void) b;
}
void mat_sum(Mat dest, Mat a, Mat b) {
	(void)dest;
	(void)a;
	(void)b;
}

void mat_print(Mat m) {
	for (size_t i = 0; i < m.rows; i++) {
		for (size_t j = 0; j < m.cols; j++) {
			printf("%f ", MAT_AT(m, i, j));
		}
		printf("\n");
	}
}

void mat_rand(Mat m, float low, float high) {
	for (size_t i = 0; i < m.rows; i++) {
		for (size_t j = 0; j < m.cols; j++) {
			MAT_AT(m, i, j) = rand_float() * (high - low) + low;
		}
	}
}



#endif //NN_IMPLEMENTATION