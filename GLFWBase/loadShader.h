#ifndef LOADSHADER_H
#define LOADSHADER_H

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <GL\glew.h>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

#endif