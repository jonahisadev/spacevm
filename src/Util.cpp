#include <VM/Util.h>

namespace VM {

    char* Util::readFile(const char* path) {
        FILE* file = fopen(path, "r");
        //ASSERT(file, "Could not open file");
        if (!file)
            return nullptr;

        fseek(file, 0, SEEK_END);
        int size = (int) ftell(file);
        fseek(file, 0, SEEK_SET);

        char* data = new char[size];
        ASSERT(data, "Could not load file");

        fread(data, sizeof(char), size, file);
        fclose(file);

		data[size] = '\0';

        return data;
    }

	unsigned char* Util::readBinFile(const char* path) {
		FILE* file = fopen(path, "rb");
        ASSERT(file, "Could not open binary file");

        fseek(file, 0, SEEK_END);
        int size = (int) ftell(file);
        fseek(file, 0, SEEK_SET);

        unsigned char* data = new unsigned char[size];
        ASSERT(data, "Could not load file");

        fread(data, sizeof(unsigned char), size, file);
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
        char* dest = new char[(end-start)+1];
        ASSERT(dest, "strDup allocation failure");

        strCopy(src, dest, start, end+1);
		dest[end] = '\0';
        return dest;
    }

	char* Util::strDupFull(char* src) {
		return strDup(src, 0, strLength(src)+1);
	}
	
	unsigned char* Util::sToB(unsigned short addr) {
		unsigned char* ret = new unsigned char[2];
		ret[0] = (addr >> 8) & 0xFF;
		ret[1] = (addr >> 0) & 0xFF;
		return ret;
	}
	
	unsigned short Util::bToS(unsigned char a, unsigned char b) {
		short x = (a << 8) | b;
		return x;
	}
	
	int Util::convertTokNum(char* str, int base) {
	    char* nStr = nullptr;
		if (base == 10)
		 	nStr = Util::strDup(str, 1, Util::strLength(str));
		else if (base == 16)
			nStr = Util::strDup(str, 2, Util::strLength(str));
		int x = (int) strtol(nStr, (char**)NULL, base);
		return x;
	}
	
	int Util::convertNum(char* str, int base) {
	    int x = (int) strtol(str, (char**)NULL, base);
	    return x;
	}

} // namespace VM