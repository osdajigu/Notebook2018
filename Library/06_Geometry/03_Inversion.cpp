pt invert (circle &c, pt p) {
    p -= c.c;
    return c.c + sqr(c.r) * p / norm(p);
}
