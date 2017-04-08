#include <VM/Util.h>

namespace VM {

    char* Util::readFile(const char* path) {
        FILE* file = fopen(path, "r");
        ASSERT(file, path);

        fseek(file, 0, SEEK_END);
        int size = (int) ftell(file);
        fseek(file, 0, SEEK_SET);

        char* data = new char[size];
        ASSERT(data, "Could not load file");

        fread(data, 1, size, file);
        fclose(file);

		data[size] = '\0';

        return data;
    }

	unsigned char* Util::readBinFile(const char* path) {
		FILE* file = fopen(path, "rb");
        ASSERT(file, "Could not open file");

        fseek(file, 0, SEEK_END);
        int size = (int) ftell(file);
        fseek(file, 0, SEEK_SET);

        unsigned char* data = new unsigned char[size];
        ASSERT(data, "Could not load file");

        fread(data, 1, size, file);
        fclose(file);

		data[size] = '\0';

        return data;
	}

    int Util::strLength(const char* a) {
        int len = 0;
        while (a[len] != '\0')
            len++;
        return len;
    }

    bool Util::strEquals(const char* a, const char* b) {
        int aLen = strLength(a);
        int bLen = strLength(b);

        if (aLen != bLen)
            return false;

        for (int i = 0; i < aLen; i++) {
            if (a[i] != b[i])
                return false;
        }

        return true;
    }

    void Util::strCopy(char* src, char* dest, int start, int end) {
        int x = 0;
        for (int i = start; i < end; i++) {
            dest[x] = src[i];
            x++;
        }
    }

    char* Util::strDup(char* src, int start, int end) {
        char* dest = (char*) malloc(sizeof(char) * (end - start));
        ASSERT(dest, "strDup allocation failure");

        strCopy(src, dest, start, end);
		dest[end] = '\0';
        return dest;
    }

	char* Util::strDupFull(char* src) {
		return strDup(src, 0, strLength(src));
	}
	
	unsigned char* Util::sToB(unsigned short addr) {
		unsigned char* ret = new unsigned char[2];
		ret[0] = (addr & 0xFF00) >> 4;
		ret[1] = (addr & 0x00FF) >> 0;
		return ret;
	}

} // namespace VM