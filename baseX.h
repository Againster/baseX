/**
 * @file baseX.h
 * @date 2016/07/19 17:47:32
 * @author lissa,lissaagainster@yahoo.com
 * @copyright lissa
 * @brief base16, base32, base64 so forth encoded/decoded
 */

#ifndef __BASE64_H__
#define __BASE64_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct baseX_s {
  unsigned char* line_separators;/**< line seperators. */
  int line_separators_length;
  int maximum_encoded_line_length;
  unsigned char padding_char;
  unsigned char* baseX_alphabet;
  int baseX_alphabet_size;
  unsigned char* baseX_ascii;
  int baseX_ascii_size;
  int group_src_size;
  int group_dst_size;
  int (*encode)(struct baseX_s* b, unsigned char*, unsigned char*);
  int (*decode)(struct baseX_s* b, unsigned char*, unsigned char*);
  unsigned char line_separators_switch : 1;
} baseX;

extern baseX base64;
extern baseX base32;
extern baseX base16;

int encode(baseX* b, unsigned char* src, int src_size, unsigned char* dst,
    int dst_size);
int decode(baseX* b, unsigned char* src, int src_size, unsigned char* dst,
    int dst_size);

void set_line_separators_switch(baseX*b, int on);
void set_pad_char(baseX* b, unsigned char padding_char);
int set_maximum_encoded_line_length(baseX* b, unsigned int length);
int set_char_for_index(baseX* b, int index, unsigned char c);

unsigned char get_char_for_index(baseX* b, int index);
int get_line_separators_switch(baseX* b);
unsigned char get_pad_char(baseX* b);
unsigned int get_maximum_encoded_line_length(baseX* b);

#ifdef __cplusplus
} /** extern "C" { */
#endif

#endif /** __BASE64_H__ */


