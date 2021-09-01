function [r] = callee(a,b)
  fprintf('callee(%f,%f)\n',a,b)
  r = a + b
end

