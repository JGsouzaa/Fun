#ifndef NN_H_
#define NN_H_

typedef struct {
	size_t rows;
	size_t cols;
	float* es;
} Mat;

Mat mat_alloc(size_t rows, size_t cols);
void mat_dot();
void mat_sum();

#endif //NN_H_

#ifndef NN_IMPLEMENTATION

#endif //NN_IMPLEMENTATION