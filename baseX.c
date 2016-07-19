#include <string.h> /** for memcpy */
#include "baseX.h"

unsigned char base16_alphabet[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F' 
};

unsigned char base16_ascii[128] = {
 /** 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 0 */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 1 */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 2 */
     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, /** 3 */
     0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 4 */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 5 */
     0,10,11,12,13,14,15, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 6 */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 7 */
};

int base16_encode(baseX* b, unsigned char* src, unsigned char* dst) {
  dst[0] = b->baseX_alphabet[(src[0] & 0x000000F0) >> 4];
  dst[1] = b->baseX_alphabet[(src[0] & 0x0000000F) >> 0];
  return 0;
}

int base16_decode(baseX* b, unsigned char* src, unsigned char* dst) {
  dst[0] = (b->baseX_ascii[src[0]] << 4) | (b->baseX_ascii[src[1]] & 0x0F);
  return 0;
}

baseX base16 = {
  .line_separators = (unsigned char*)"\r\n",
  .line_separators_length = sizeof("\r\n") - 1,
  .maximum_encoded_line_length = 76,
  .padding_char = '=',
  .baseX_alphabet = base16_alphabet,
  .baseX_alphabet_size = sizeof(base16_alphabet),
  .baseX_ascii = base16_ascii,
  .baseX_ascii_size = sizeof(base16_ascii),
  .group_src_size = 1,
  .group_dst_size = 2,
  .encode = base16_encode,
  .decode = base16_decode,
  .line_separators_switch = 1
};

unsigned char base32_alphabet[32] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K',
    'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X',
    'Y', 'Z'
};

unsigned char base32_ascii[128] = {
 /** 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 0 */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 1 */
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 2 */
     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, /** 3 */
     0,10,11,12,13,14,15,16,17, 1,18,19, 1,20,21, 0, /** 4 */
    22,23,24,25,26, 0,27,28,29,30,31, 0, 0, 0, 0, 0, /** 5 */
     0,10,11,12,13,14,15,16,17, 1,18,19, 1,20,21, 0, /** 6 */
    22,23,24,25,26, 0,27,28,29,30,31, 0, 0, 0, 0, 0  /** 7 */
};

int base32_encode(baseX* b, unsigned char* src, unsigned char* dst) {
  dst[0] = b->baseX_alphabet[(src[0] & 0xF8) >> 3];
  dst[1] = b->baseX_alphabet[(src[0] & 0x07) << 2 | (src[1] & 0xC0) >> 6];
  dst[2] = b->baseX_alphabet[(src[1] & 0x3E) >> 1];
  dst[3] = b->baseX_alphabet[(src[1] & 0x01) << 4 | (src[2] & 0xF0) >> 4];
  dst[4] = b->baseX_alphabet[(src[2] & 0x0F) << 1 | (src[3] & 0x80) >> 7];
  dst[5] = b->baseX_alphabet[(src[3] & 0x7C) >> 2];
  dst[6] = b->baseX_alphabet[(src[3] & 0x03) << 3 | (src[4] & 0xE0) >> 5];
  dst[7] = b->baseX_alphabet[(src[4] & 0x1F) >> 0];
  return 0;
}


int base32_decode(baseX* b, unsigned char* src, unsigned char* dst) {
  dst[0] = b->baseX_ascii[src[0]] << 3 | b->baseX_ascii[src[1]] >> 2;
  dst[1] = (b->baseX_ascii[src[1]] & 0x03) << 6 | b->baseX_ascii[src[2]] << 1 |
           b->baseX_ascii[src[3]] >> 4;
  dst[2] = (b->baseX_ascii[src[3]] & 0x0F) << 4 | b->baseX_ascii[src[4]] >> 1;
  dst[3] = (b->baseX_ascii[src[4]] & 0x01) << 7 | b->baseX_ascii[src[5]] << 2 |
           (b->baseX_ascii[src[6]] & 0x18) >> 3;
  dst[4] = (b->baseX_ascii[src[6]] & 0x07) << 5 | b->baseX_ascii[src[7]] >> 0;
  return 0;
}

baseX base32 = {
  .line_separators = (unsigned char*)"\r\n",
  .line_separators_length = sizeof("\r\n") - 1,
  .maximum_encoded_line_length = 64,
  .padding_char = '=',
  .baseX_alphabet = base32_alphabet,
  .baseX_alphabet_size = sizeof(base32_alphabet),
  .baseX_ascii = base32_ascii,
  .baseX_ascii_size = sizeof(base32_ascii),
  .group_src_size = 5,
  .group_dst_size = 8,
  .encode = base32_encode,
  .decode = base32_decode,
  .line_separators_switch = 1
};

unsigned char base64_alphabet[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', '+', '/'
};

unsigned char base64_ascii[128] = {
 /** 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 1 */
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 2 */
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,62, 0, 0, 0,63, /** 3 */
		52,53,54,55,56,57,58,59,60,61, 0, 0, 0, 0, 0, 0, /** 4 */
		 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14, /** 5 */
		15,16,17,18,19,20,21,22,23,24,25, 0, 0, 0, 0, 0, /** 6 */
		 0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40, /** 7 */
		41,42,43,44,45,46,47,48,49,50,51, 0, 0, 0, 0, 0  /** 8 */
};

int base64_encode(baseX* b, unsigned char* src, unsigned char* dst) {
  dst[0] = b->baseX_alphabet[src[0] >> 2];
  dst[1] = b->baseX_alphabet[(src[0] & 0x03) << 4 | src[1] >> 4];
  dst[2] = b->baseX_alphabet[(src[1] & 0x0F) << 2 | src[2] >> 6];
  dst[3] = b->baseX_alphabet[(src[2] & 0x03F)];
  return 0;
}

int base64_decode(baseX* b, unsigned char* src, unsigned char* dst) {
  dst[0] = b->baseX_ascii[src[0]] << 2 | b->baseX_ascii[src[1]] >> 4;
  dst[1] = (b->baseX_ascii[src[1]] & 0x0F) << 4 | b->baseX_ascii[src[2]] >> 2;
  dst[2] = (b->baseX_ascii[src[2]] & 0x03) << 6 | b->baseX_ascii[src[3]];
  return 0;
}

baseX base64 = {
  .line_separators = (unsigned char*)"\r\n",
  .line_separators_length = sizeof("\r\n") - 1,
  .maximum_encoded_line_length = 76,
  .padding_char = '=',
  .baseX_alphabet = base64_alphabet,
  .baseX_alphabet_size = sizeof(base64_alphabet),
  .baseX_ascii = base64_ascii,
  .baseX_ascii_size = sizeof(base64_ascii),
  .group_src_size = 3,
  .group_dst_size = 4,
  .encode = base64_encode,
  .decode = base64_decode,
  .line_separators_switch = 1
};

void set_line_separators_switch(baseX* b, int on) {
  b->line_separators_switch = on;
};

void set_pad_char(baseX* b, unsigned char c) { b->padding_char = c; };

int set_maximum_encoded_line_length(baseX* b, unsigned int length) {
  if (length && !(length % b->group_dst_size)) {
    b->maximum_encoded_line_length = length;
    return 1;
  }
  return 0;
};

int set_char_for_index(baseX* b, int index, unsigned char c) {
  if (index < b->baseX_alphabet_size && c < b->baseX_ascii_size) {
    b->baseX_ascii[b->baseX_alphabet[index]] = '\0'; /**< erase previous
                                                     letter->number map to 
														                         keep unique map.*/
    b->baseX_alphabet[index] = c;
    b->baseX_ascii[c] = index;
    return 1;
  }
  return 0;
};

unsigned char get_char_for_index(baseX* b, int index) {
  return b->baseX_alphabet[index];
};

int get_line_separators_switch(baseX* b) { return b->line_separators_switch; };

unsigned char get_pad_char(baseX* b) { return b->padding_char; };

unsigned int get_maximum_encoded_line_length(baseX* b) {
  return b->maximum_encoded_line_length;
};

int encode(baseX* b, unsigned char* src, int src_size, unsigned char* dst,
    int dst_size) {
  int i, j, k, size_group;
  unsigned char* p;
  const int max_size_group_src = b->maximum_encoded_line_length /
                                 b->group_dst_size * b->group_src_size;
  const int max_size_group_dst = b->maximum_encoded_line_length + 
                                 (b->line_separators_switch ?
                                  b->line_separators_length : 0);
  const int count_group = src_size % max_size_group_src ? 
                          src_size / max_size_group_src + 1:
                          src_size / max_size_group_src;
  const int size_padding = (b->group_src_size - src_size % b->group_src_size) %
                            b->group_src_size;
  const int size_result = ((src_size + size_padding) / b->group_src_size *
                           b->group_dst_size) +
                          (b->line_separators_switch ?
                           (count_group - 1) * b->line_separators_length : 0);
  for (i = 0; i < count_group; i++)  {
    j = 0;
    k = i * max_size_group_dst;
    p = src + i * max_size_group_src;
    size_group = max_size_group_src;
    /// last group
    if (i == count_group - 1) { 
      size_group = src_size % max_size_group_src + size_padding;
      if (size_padding) {
        p = dst + size_result;
        memset(p - b->group_src_size, 0, b->group_src_size);
        p -= size_group;
        memcpy((void*)p, (void*)(src + i * max_size_group_src),
            src_size % max_size_group_src);
      }
    }
    /// kernel
    while (j < size_group) {
      b->encode(b, p + j, dst + k);
      j += b->group_src_size;
      k += b->group_dst_size;
    }
  }
  /// padding
  for (i = 0; i < size_padding; i++) {
    dst[size_result - 1 - i] = b->padding_char;
  }
  /// line separators
  if (b->line_separators_switch) {
    for (i = 1; i < count_group; i++) { /// skip last group
      for (j = 0; j < b->line_separators_length; j++) {
        dst[i * max_size_group_dst - b->line_separators_length + j] =
          b->line_separators[j];
      }
    }
  }
  return size_result;
}

int decode(baseX* b, unsigned char* src, int src_size, unsigned char* dst,
    int dst_size) {
  int i, j, k, size_group;
  unsigned char* p;
  const int max_size_group_src = b->maximum_encoded_line_length +
                                 (b->line_separators_switch ? 
                                  b->line_separators_length : 0);
  const int max_size_group_dst = b->maximum_encoded_line_length /
                                 b->group_dst_size * b->group_src_size;
  const int count_group = src_size / max_size_group_src + 
                          (src_size % max_size_group_src ? 
                           1 : 0);
  int size_padding, size_result;
  /// count padding
  for (i = 0, size_padding = 0; i < b->group_dst_size; i++) {
    if (src[src_size - i - 1] != b->padding_char)
      break;
    size_padding++;
  }
  /// result
  size_result = (src_size - (b->line_separators_switch ?
                            ((count_group - 1) * b->line_separators_length) : 0)                ) / b->group_dst_size * b->group_src_size - size_padding;
  for (i = 0; i < count_group; i++) {
    /// last group
    if (count_group - 1 == i && (src_size % max_size_group_src))
      size_group = src_size % max_size_group_src;
    else
      size_group = b->maximum_encoded_line_length;
    j = 0;
    k = i * max_size_group_dst;
    p = src + i * max_size_group_src;
    while (j < size_group) {
      /// kernel
      b->decode(b, p + j, dst + k);
      j += b->group_dst_size;
      k += b->group_src_size;
    }
  }
  return size_result;
}

