#miniprintf is make my printf

#format specifier := %[flags][width][.precision][type-prefix]type
#where flag := { + | - | 0 }
#     flags := one or more flag
#      width := a decimal number
#      precision := a decimal number
#      type-prefix := { h | l }
#      type := { c | s | b | d | x | X | % }
#
#[] indicates as optional.
#
#TYPE
#	c - take an argument and print it as a character
#	s - take an argument and print it as a character string
#	b - take an argument and print it as a binary number
#	d - take an argument and print it as a decimal number
#	x - take an argument and print it as a hexadecimal number in lower-case
#	X - take an argument and print it as a hexadecimal number in upper-case
#	% - print a single percent sign. takes no argument. ignores flags, width, precision, type-prefix.
#
#SAMPLE
#	mini_printf ("hello, world\n");                      hello, world
#	mini_printf ("[%99% %T %d]\n", 20);                  [% %T 20]
#	mini_printf ("[%d %x %X %b]\n", 15, 15, 15, 15);     [15 f F 1111]
#	mini_printf ("[%+010ld]\n", 999l);                   [+000000999]
#	mini_printf ("[%+010.005ld]\n", -999l);              [    -00999]
#	mini_printf ("[%10.6b]\n", 16);                      [    010000]
#	mini_printf ("[%.6s]\n", "hello, world");            [hello,]
#	mini_printf ("[%10.6s]\n", "hello, world");          [    hello,]
#	mini_printf ("[%4.6s]\n", "hello, world");           [hello,]
#	mini_printf ("[%4.0s]\n", "hello, world");           [    ]
#	mini_printf ("[%9s]\n", "hello, world");             [hello, world]
#	mini_printf ("[%-20s]\n", "hello, world");           [hello, world        ]
#	mini_printf ("[%20s]\n", "hello, world");            [        hello, world]
#	mini_printf ("[%~s]\n", "hello");                    [olleh]
#	mini_printf ("[%~20s]\n", "hello");                  [               olleh]
#	mini_printf ("[%~-20s]\n", "hello");                 [olleh               ]
#	mini_printf ("[%~-20.3s]\n", "hello");               [oll                 ]
#	mini_printf ("[%4.6c]\n", 'A');                      [   A]
#	mini_printf ("[%4.0c]\n", 'A');                      [   A]
#	mini_printf ("[%-20c]\n", 'A');                      [A                   ]
#	mini_printf ("[%+10x]\n", -1);                       [  ffffffff]
#
#