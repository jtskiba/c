#!/usr/local/bin/perl
# converts list of decimals into hex

for ($i = 0; $i < @ARGV; $i++){
	printf("%d\t= 0x%x\n", $ARGV[$i], $ARGV[$i]);
}
