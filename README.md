# Fractaler

A real-time fractal explorer built with raylib. Left click to zoom in, right click to zoom out, `R` to reset view. Select an algorithm and configure its parameters, then press **Start** to render.

---

## Parameters

| Parameter | Description |
|-----------|-------------|
| **P** | Primary exponent or power |
| **Q** | Secondary exponent (paired with P) |
| **cx** | Real part of the complex constant c |
| **cy** | Imaginary part of the complex constant c |
| **delta** (λ) | Mode switch — changes fractal behavior when non-zero |
| **polynomial** | Custom polynomial string (used by Newton and Nova) |
| **iterations** | Maximum number of iterations before a point is considered bounded |

---

## Fractals

### Multibrot
General Mandelbrot-family fractal. Iterates `z = z^P + c`.

| Parameter | Effect |
|-----------|--------|
| P | Exponent. P=2 gives the classic Mandelbrot set |
| delta (λ) | 0 = normal iteration, non-zero = conjugate of z^P is used instead |

---

### Julia
Julia set counterpart to Multibrot. Iterates `z = z^P + c` where c is fixed.

| Parameter | Effect |
|-----------|--------|
| P | Exponent |
| cx, cy | The fixed complex constant c. Controls which Julia set is rendered |

---

### Burning Ship
Absolute-value variant. Iterates `z = |z|^P - c` where both components of z are made positive before each step.

| Parameter | Effect |
|-----------|--------|
| P | Exponent |
| cx, cy | If both are 0, c follows the plotted point (Mandelbrot-style). Otherwise c is fixed (Julia-style) |

---

### Newton
Newton's method applied to a polynomial. Converges to roots; colors by iteration count to convergence.

| Parameter | Effect |
|-----------|--------|
| polynomial | The polynomial to find roots of (e.g. `(1+0i)z^3-(1+0i)`) |

---

### Nova
Generalized Newton fractal with an additive term. Iterates `z = z - (P,iQ)*(f(z)/f'(z)) + c`.

| Parameter | Effect |
|-----------|--------|
| P, Q | Real and imaginary parts of the relaxation factor a |
| cx, cy | The additive constant c |
| delta (λ) | 0 = z starts at the plotted point, non-zero = z starts at (cx, cy) |
| polynomial | The polynomial f(z) |

---

### Sin
Sine-based fractal.

| Parameter | Effect |
|-----------|--------|
| P | Exponent applied after sine |
| cx, cy | Complex constant c |
| delta (λ) | 0 = multiplicative mode `sin(z)^P * c`, non-zero = additive mode `sin(z)^P + c`. λ also scales the bailout threshold |

---

### Sinh
Hyperbolic sine variant of the sine fractal. Iterates `sinh(z)^P + c`.

| Parameter | Effect |
|-----------|--------|
| P | Exponent applied after sinh |
| cx, cy | Complex constant c |
| delta (λ) | 0 = standard bailout, non-zero = λ scales the bailout threshold |

---

### Newton Cosh
Newton's method applied to `cosh(z) - 1`, using `sinh(z)` as the derivative.

| Parameter | Effect |
|-----------|--------|
| — | No user parameters. Behavior is fixed |

---

### Collatz
Complex extension of the Collatz conjecture. Uses imaginary part as bailout condition.

| Parameter | Effect |
|-----------|--------|
| — | No user parameters. Behavior is fixed |

---

### Septagon
Rational map with a 7th power. Iterates `(z^7 + φ) / z`.

| Parameter | Effect |
|-----------|--------|
| — | No user parameters. φ is fixed at -0.14 |

---

### Magnet 1
Magnetic pendulum fractal (order 1). Iterates a rational map derived from magnetic models.

| Parameter | Effect |
|-----------|--------|
| delta (λ) | 0 = Mandelbrot-style (z starts at 0, c follows point), non-zero = Julia-style (z follows point, c fixed at cx/cy) |
| cx, cy | Fixed c for Julia-style mode |

---

### Magnet 2
Magnetic pendulum fractal (order 2). Higher-order version of Magnet 1.

| Parameter | Effect |
|-----------|--------|
| delta (λ) | 0 = Mandelbrot-style, non-zero = Julia-style |
| cx, cy | Fixed c for Julia-style mode |

---

### Cactus
Cubic map with a dependency on the initial point. Iterates `z^3 + z*(c-1) - c`.

| Parameter | Effect |
|-----------|--------|
| — | No user parameters. c is the plotted point itself |

---

### Lambda
Logistic map in the complex plane. Iterates `a * z * (1 - z)`.

| Parameter | Effect |
|-----------|--------|
| cx, cy | The complex multiplier a. Controls the shape significantly |

---

### Barnsley Tree
Barnsley fractal tree via a complex affine map. Iterates `a * (z - sign(Re(z)))`.

| Parameter | Effect |
|-----------|--------|
| cx, cy | The complex multiplier a |

---

### Rings
Rational spiral map. Iterates `(z^2 * (z^2 + σ) * e) / (σ*z^2 + 1)` where e is a fixed rotation.

| Parameter | Effect |
|-----------|--------|
| P | Controls σ = √P, which scales the ring spacing |

---

### Roger Rational
Highly composite rational map producing intricate ring-like structures.

| Parameter | Effect |
|-----------|--------|
| P | Scales the internal rational function g(z) = 1/(z*P) |

---

### Spiral Julia
Julia set using `tan(z^2 + c)`. Produces spiral structures around singularities.

| Parameter | Effect |
|-----------|--------|
| cx, cy | The complex constant c |

---

### Tetration
Infinite power tower. Iterates `z^zn` (z to the power of itself repeatedly).

| Parameter | Effect |
|-----------|--------|
| — | No user parameters. Bailout is on real components |

---

### Triple Dragon
Rational map producing dragon-like structures. Iterates `z^3/(z^3+1) + c`.

| Parameter | Effect |
|-----------|--------|
| cx, cy | The complex constant c |

---

### Phoenix
Two-term recurrence fractal. Iterates `zn+1 = zn^2 + c + (P,iQ)*zn-1`.

| Parameter | Effect |
|-----------|--------|
| cx, cy | The complex constant c |
| P, Q | Real and imaginary parts of the previous-iteration weight |

---

## Controls

| Input | Action |
|-------|--------|
| Left click | Zoom in toward cursor |
| Right click | Zoom out from cursor |
| R | Reset zoom to default view |
| Start button | Apply current parameters and re-render |
