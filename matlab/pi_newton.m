r = 1;
c = [r, 0];
x = 0:0.01:2*r;
dt = 1e-5;

function y = circle(x, r, c)
    % (x - c(1))^2 + (y - c(2))^2 = r^2
    y = c(2) + sqrt(r^2 - (x - c(1)).^2);
end

y = circle(x, r, c);

M = 0;
for t = 0:dt:(r/2)
    M = M + dt * circle(t, r, c);
end

A = ((r/2)*(r*sqrt(3)/2)) / 2;

pi_aprox = 6 * (M + A) / (r^2)
pi - pi_aprox

hold on;
grid on;
plot(x,y)

pA = [r/2, 0];
pB = [r/2, circle(r/2, r, c)];
pO = [c(1), c(2)];

area(0:0.01:r/2, circle(0:0.01:r/2, r, c))
area([pA(1) pB(1) pO(1)], [pA(2) pB(2) pO(2)])

text_pA = text(pA(1), pA(2), "A(r/2, 0)");
text_pB = text(pB(1), pB(2), "B(r/2, r*√3/2)");
text_pO = text(pO(1), pO(2), "O(r, 0)");

for p = [text_pA text_pB text_pO]
    set(p, "color", "blue");
    set(p, "fontsize", 20);
    set(p, "fontweight", "bold");
    set(p, "linestyle", "-");
end

hold off
