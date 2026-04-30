#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <sysutil/sysutil.h>

int disk_ok() {
    struct statvfs v;
    if (statvfs("/dev_hdd0/", &v) < 0) return 0;
    return ((v.f_bsize * v.f_bfree) / (1024 * 1024) > 15);
}

void apply_patch(const char* path, long offset, uint8_t value) {
    if (!disk_ok()) return;
    char tmp[256];
    snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    FILE *src = fopen(path, "rb"), *dst = fopen(tmp, "wb");
    if (src && dst) {
        char b; while(fread(&b, 1, 1, src)) fwrite(&b, 1, 1, dst);
        fclose(src); fclose(dst);
        FILE *f = fopen(tmp, "rb+");
        fseek(f, offset, SEEK_SET);
        fwrite(&value, 1, 1, f);
        fsync(fileno(f)); 
        fclose(f);
        rename(tmp, path);
    }
}

int main() {
    msgType mt = {0};
    xmb_notify(xmb_itoken_get(), mt, "🐍 Master-Cobra-AI v7.0: ACTIVO");
    return 0;
}
