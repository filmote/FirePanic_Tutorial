#pragma once

#define BOTTOM_ARC_1 11
#define BOTTOM_ARC_2 33
#define BOTTOM_ARC_3 55
#define TOP_ARC_1_2 22
#define TOP_ARC_2_3 44

#define PYHSICS_ARC_NO_OF_ELEM 75

const uint8_t PROGMEM Physics_Arc_1_1[22] = {
18, 1,    /* 00 */ 
19, 1,    /* 01 */ 
20, 1,    /* 02 */ 
21, 1,    /* 03 */ 
22, 2,    /* 04 */ 
23, 4,    /* 05 */ 
24, 7,    /* 06 */ 
25, 11,   /* 07 */ 
26, 16,   /* 08 */ 
27, 23,   /* 09 */ 
28, 30,   /* 10 */ 
};

const uint8_t PROGMEM Physics_Arc_2_1[22] = {
18, 15, 	
19, 11, 	
20, 7, 	
21, 4, 	
22, 3, 	
23, 4, 	
24, 7, 	
25, 11, 
26, 23, 	
27, 27, 	
28, 32, 
};

const uint8_t PROGMEM Physics_Arc_3_1[22] = {
18, 25, 	
19, 21, 	
20, 18, 	
21, 16, 	
22, 15, 
23, 16, 	
24, 18, 	
25, 20, 	
26, 23, 	
27, 27, 	
28, 32, 
};

const uint8_t PROGMEM Physics_Arc_2[(PYHSICS_ARC_NO_OF_ELEM - 11) * 2] = {
29, 37,   /* 11 Bottom of 1 */ 
30, 32,   /* 12 */ 
31, 27,   /* 13 */ 
32, 22,   /* 14 */ 
33, 17,   /* 15 */ 
34, 12,   /* 16 */ 
35, 8,    /* 17 */ 
36, 5,    /* 18 */ 
37, 3,    /* 19 */ 
38, 2,    /* 20 */ 
39, 1,    /* 21 */ 
41, 1,    /* 22 */ 
42, 2,    /* 23 */ 
43, 3,    /* 24 */ 
44, 5,    /* 25 */ 
45, 7,    /* 26 */ 
46, 10,   /* 27 */ 
47, 13,   /* 28 */ 
48, 17,   /* 29 */ 
49, 22,   /* 30 */
50, 27,   /* 31 */ 
51, 33,   /* 32 */ 
52, 37,   /* 33 Bottom of 2 */ 
53, 33,   /* 34 */ 
54, 30,   /* 35 */ 
55, 26,   /* 36 */ 
56, 22,   /* 37 */ 
57, 18,   /* 38 */ 
58, 14,   /* 39 */ 
59, 11,   /* 40 */ 
60, 9,    /* 41 */ 
61, 8,    /* 42 */ 
62, 7,    /* 43 */ 
63, 7,    /* 44 */ 
64, 7,    /* 45 */ 
65, 8,    /* 46 */ 
66, 9,    /* 47 */ 
67, 11,   /* 48 */ 
68, 14,   /* 49 */
69, 18,   /* 50 */ 
70, 22,   /* 51 */ 
71, 26,   /* 52 */ 
72, 30,   /* 53 */ 
73, 33,   /* 54 */ 
74, 37,   /* 55 Bottom of 3 */ 
75, 34,   /* 56 */ 
76, 31,   /* 57 */ 
77, 28,   /* 58 */ 
78, 26,   /* 59 */ 
79, 24,   /* 60 */ 
81, 22,   /* 61 */ 
83, 21,   /* 62 */ 
85, 20,   /* 63 */ 
87, 20,   /* 64 */ 
89, 20,   /* 65 */ 
91, 20,   /* 66 */ 
93, 21,   /* 67 */ 
95, 22,   /* 68 */ 
97, 24,   /* 69 */ 
98, 26,   /* 70 */ 
99, 28,   /* 71 */ 
100, 31,  /* 72 */ 
101, 34,  /* 73 */ 
102, 37,  /* 74 */ 
};

const uint8_t* const Physics_Arc_1[] = { Physics_Arc_1_1, Physics_Arc_2_1, Physics_Arc_3_1 };
