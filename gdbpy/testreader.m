%% Octave/Matlab test a a generated C-struct reader

fprintf("Test sread\n");

f = fopen('out.bin', 'r');
s.f1 = fread(f, [1:1], 'single');
fclose(f);
disp(s);

f = fopen('out.bin', 'r');
s1 = sread_internal(f);
s2 = sread_internal(f);
fclose(f);
disp(s1);
disp(s2);

quit
