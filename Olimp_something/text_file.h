#pragma once

#include <stdio.h>

#include "utils.h"

struct TextFile {
    FILE* file;

    TextFile()
        : file(NULL)
    {}

    bool open(const String& path, const char* mode="r") {
        file = fopen(path.str(), mode);
        return is_open();
    }

    bool is_open() const {
        return file != NULL;
    }

    String read_line() {
        if (!is_open()) {
            return "";
        }
        String result;
        while (true) {
            char p;
            int size = fread(&p, 1, 1, file);
            if (size == 0) {
                return result;
            }
            result += p;
            if (p == '\n') {
                return result;
            }
        }
    }

    void close() {
        if (is_open()) {
            fclose(file);
            file = NULL;
        }
    }

    ~TextFile() {
        close();
    }
};
