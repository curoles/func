#pragma once

extern inline
bool hasstr(const char* s, const char* a[], size_t len)
{
    for (unsigned i = 0; i < len && a[i] != NULL; ++i) {
        if (0 == strcmp(s, a[i])) return true;
    }

    return false;
}

