teams = char('Packers' , 'Giants' , 'Bears' , 'Steelers' , 'Redskins');
wins = [2 ; 8 ; 8 ; 6 ; 6]
p = barh(wins)
xlabel('Championships')
title('NFL Teams with Most Championships','fontsize',24)
for i=1:5,
    gtext(teams(i,:))
end