void line(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0), plus_x = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), plus_y = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2;
  int e2;

  for (;;) {
    setPixel(x0, y0);
    if (x0 == x1 && y0 == y1) break;

    e2 = err;
    if (e2 > -dx) {
      err -= dy;
      x0 += plus_x;
    }
    if (e2 < dy) {
      err += dx;
      y0 += plus_y;
    }
  }
}
