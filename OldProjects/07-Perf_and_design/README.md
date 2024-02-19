# 7 Performance and Design break;


## Description:
In this project, I’m not going to add any new features.  I want to take a break to wrap my head around the design so far and do some performance profiling.

## Perf stats:
First I added a timer to the main function to measure the execution time of the loop.  I ran it three times in release mode and got the following times - 11.67 s, 11.23 s, 11.41s.
### 1. Play with compiler flags.  
/Od  gives me 11.98 s.  /Ot gives me 11.71 s.  No help there.
### 2. Let’s do some profiling.
* 97% in Raytracer::trace().  No surprise there 
* 18% instersects_with - 13% is in Rect intersects_with
* 5% reflects
* 7% lightdir.normalize().  Oh that sqrt function.
* 54% in the specular intensity equation
```cpp
float specular_light_intensity = std::powf(std::max(0.f, (-reflect(-lightDir, nearestReflection->norm)).dot(primary_ray.dir)), pNearestShape->properties.specular_exp) * secondary_shape->properties.intensity;
```
Ok, so why is this equation taking so much time?  If I remove the equation completely and just set specular intensity to zero, the program take 4.3 s.  Two thirds of my program is spent in that equation!!!  I split it up and narrowed it down to std::powf().  Powf uses a Taylor series expansion which seems like overkill if the exponent is an int.  I switched to std::pow() which is overloaded to take an integer exponent but it still runs slow.

I’m going to write my own pow(val, exp) function.  I could just multiply the value by itself ‘exp’ times, but some of my exponents may be up to 1000.  I think 1000 multiply operations would be slower than a Taylor series expansion.  But something I notice is that the answer doesn’t need to be amazingly precise.  The answer is going to be somewhere between zero and one so I can fudge it a bit.  I wrote a pow function that rounds the exponent to the next power of 2.  For example, if exp is 10, it’ll calculate val to the 16th power:  val2 = val * val; val4 = val2 * val2, val8 = val4 * val4; val16 = val8 * val8;  Quick and dirty, but close enough.
```cpp
float myPow(float val, int exp) {
  int curexp = 1;
  float curval = val;
  while (curexp < exp) {
    curval *= curval;
    curexp *= 2;
  }
  return curval;
}
```

### 3. Now let’s mess with the recursive depth of the trace() function.  
The default is 5 which takes 11.4 s.
* 1 is 2.9 s but obviously, the mirrors won’t work.
* 10 is 23.1 s with no apparent improvement over depth=5.
* Somewhere between 3 and 5 seems like a good value for now.

### 4. Get rid of unnecessary code
I had some unnecessary code in Reflect() that always makes sure the norm is pointing in the correct direction.  I removed that code and got a non trivial improvement.  Down from 11.4 to 10.7 s.  Not much, but I’ll take it.

### 5. There’s a lot of stuff going on in the secondary_shape loop.  
I adjusted it to only run on shapes that have a non-zero light intensity.  Since there are only two light sources in the scene, this gave me a significant improvement.  6.3 s.

### 6. If I apply all of the above, the program runs in 1.9 s.  
About 1/6 of the original run time of 11.9 s.  Now when I profile again, the barycentric_intersects function is taking 55% of the total run time.  This makes sense since it is being called several times for each pixel.  I think that if I make a small improvement to this function, I’ll see a noticeable improvement.  

The top of the barycentric_intersects() function calculates the basis vectors of the barycentric coordinate system and the norm of the surface. This can all be done when the Shape is constructed so I moved it into the Triangle and Rectangle constructors and changed the signature of barycentric_intersects() to accept these parameters. The profiler shows less work is happening in the function now but the runtime is still an average of 1.9 s. 

### 7.  std::function is slow and painful
The std::function in barycentric intersects is eating up more than its share of cpu time.  I was using a std::function so that I could pass a lambda to the function.  I got rid of the std::function and am instead using template type deduction for the lambda.  This eliminates the dynamic allocation and other overhead that comes with std::function.  Plus, by preserving the type, the compiler can inline the lambda.  This brings run time down to 1.4 s.

[Compiler explorer example of a lambda being inlined when passed to a function using template type deduction](https://godbolt.org/z/ap6awX)
