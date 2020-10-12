function x = e6_page119(n)
if n<=1
  x = 1;
else
  x = n .* e6_page119(n-1) ;
end