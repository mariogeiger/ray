ti = linspace(0, pi/2, 1000);
n1 = 1.2; % from
n2 = 1; % to

tt = asin(n1 * sin(ti) / n2);

% senkrecht (perpendicular)
Rs = abs((n1*cos(ti) - n2*cos(tt))./(n1*cos(ti) + n2*cos(tt))).^2;

% parallel
Rp = abs((n1*cos(tt) - n2*cos(ti))./(n1*cos(tt) + n2*cos(ti))).^2;

