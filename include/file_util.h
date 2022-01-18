#pragma once
#include <stdio.h>
#include "string_util.h"

using file = FILE;

file* custom_fopen(string path, string mode);