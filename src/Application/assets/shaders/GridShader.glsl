
// The GRID define determines how many grid cells (squared)
// appear in each quadrant of the graph within the range
// -1.0 to 1.0 (default: 5)
//
// NOTE: If the amount is too high, then there may not be enough
// resolution on the canvas to actually draw them all
#define GRID 5.0

// The SMOOTH define determines the border smoothness of
// the actual graphed line (default: 0.005)
#define SMOOTH 0.005

// The THICKNESS define determines the actual thickness
// of the graphed line (default: 0.01)
#define THICKNESS 0.01

// This would be best initialized as a uniform variable
// however, WebGL does not allow the initialization of 
// uniforms in the shader. GRAPH_COLOR represents the color
// of the graph to be drawn (default: vec3(0.191, 1.000, 0.461))
#define GRAPH_COLOR vec3(0.191, 1.000, 0.461)

// This is only required for WebGL which was what this was
// programmed for.
#ifdef GL_ES
precision mediump float;
#endif

// u_resolution:
//	- a 2 component vector sent as a uniform once at the
//	  beginning of the CPU program. It contains the resoltion
//	  in pixels of the canvas being drawn to.
uniform vec2 u_resolution;

// The actual function that is to be graphed
//
//		@param - x: specifies the input for `f(x)`
//		@return - float: specifies the output
//
// This function returns the y-pixel coordinate that the graph
// should contain given an input value x
float function(float x) {
    
    return sin(x);
    
}

// The following function acts as a sharpening function for
// images.
//
//		@param - x: specifies the input (must be within the range [0, 1])
//		@return - float: specifies the output of the function
//
// This function is pretty muched only used to make the grid lines
// look a bit sharper, otherwise they look a bit blurry
//
float sharpen(float x) {
    
    // The function is called the fade function and is taken
    // from Ken Perlin's Perlin noise algorithm. I have simply
    // found it a different use. (5x^6 - 15x^4 + 10x) 
    return x * x * x * (x * (6.0 * x - 15.0) + 10.0);
    
}

// Ouputs a value between 0.0 and 1.0 to determine how much of the specified
// pixel should be drawn as the graph color (effectively plotting the graph on the canas)
//
//		@param - pixel: specifies the pixel that will be tested
//		@return - float: outputs a value between 0.0 and 1.0 determining
//						 how much the specified pixel contributes to the shape
//						 of the graph
//
// This function also smooths the output value 
float plot(vec2 pixel) {
	return (
        
        // The function works by using the previously defined SMOOTH and THICKNESS constants
        //
        // 		It uses the actual `function` function to determine the y-coordinate
        // 		of the pixel that should be drawn given an x coordinate
        //
        //		Then given that y value, the output is used as an input for the smoothstep
        //		function, which has the following declaration: 
        //
        //			smoothstep(genType edge0, genType edge1, genType x)
        //
        //		the output of this function is some value between `edge0` and `edge` based
        //		on the `x` input (which in this case is the output of the `function` function)
        //
        //		The `edge0` and `edge1` parameters are calculated using the y-coordinate of the
        //		pixel passed in as the `pixel` parameter. The following call of the smoothstep
        //		function:
        //
        smoothstep(pixel.y - THICKNESS - SMOOTH, pixel.y - THICKNESS, function(pixel.x)) - 
        //
        //		calulates the upper-bound of the graph. What is this? Well, since the graph
        //		has an actual thickness value (even though in reality a line has no thickness, 
    	//		but we want to actually be able to see the line, so we give it thickness), then
        //		technically the graph has two sides. Effectively, what we're doing is we're
        //		drawing two different copies of the graph each of which are slightly shifted in
        //		either direction from the original parent graph. We then subtract the lower bound
        //		from the upper bound, which is calculated by the following:
        //		
        smoothstep(pixel.y + THICKNESS, pixel.y + THICKNESS + SMOOTH, function(pixel.x))
        //		
        //		the SMOOTH define is used to increase the width of the Hermite function
        //		(which is what `smoothstep` uses) therefore effectively increasing the
        //		*gradual* change in values (that is, smoothness)
        //
        //		the THICKNESS define is used to increase the separation between the two shifted
        //		copies of the graph (which was described earlier), therefore increasing the
        //		apparent thickness of the graph.
        //
        //		By subtracting the lower bound from the upper bound, we are are only keeping the 
        //		parts where the graphs actually overlap, which should create a visible area
        //		containing the original graph.
        //
        //		Since the `smoothstep` function returns a value from 0.0 to 1.0 and the upper bound
        //		will always be greater than the lower bound, this function will always return a value 
        //		from 0.0 to 1.0
        //
        //		You are encourage to comment out the lower bound and the upper bound just to see
        //		what effects they have on the graph. Also you are encourage to look up the glsl
        //		`smoothstep` function to see how it works.
    
    );
}

void main() {

    // Store the 2D coordinate of the current instance fragment in a vec2 called `st`
    vec2 st = gl_FragCoord.xy;
    
    // normalize the `st` vector by dividing by the 2D resolution contained in the
    // u_resolution uniform. By default, the normalization will be from 0.0 to 1.0
    // so the graph will show the first quadrant of the cartesian coordinate plane
    // and both x and y axes will go from 0.0 to 1.0. Optionally you can shift and
    // enlargen the range like I did (I increased the size by 4.0 and shifted both
    // the x and y axes by 2.0 in order to show all quadrants). In this case,
    // both the x and y axes extend from -2.0 to 2.0.
    //
    st = st / u_resolution * 4.0 - vec2(2.0, 2.0);
    
    // The following creates a grid in pretty much the same way the `plot` function
    // works. It uses a function. the `fract` function returns the fractional part
    // of the operation. Because of it's nature, it loops between 0.0 and < 1.0 therefore
    // creating a tiling pattern
    //
    // the coordinate of the instance pixel is multiplied by the GRID constant in order
    // to determine how many times the `fract` function should loop, therefore determining
    // how many grid tiles there will be.
    //
    // the glsl `step(genType edge, genType x);` function, unlike `smoothstep`, will return *either* 0.0 or 1.0
    // and nothing else if the x variable is less than the `edge` parameter, then the function will return 0.0
    // 1.0 otherwise.
    //
    // the fract output is subtracted by 0.4 (arbitrary value) and absoluted to now return values between
    // 0.0 and <0.6. Since the step function's edge is 0.5, then only values greater than 0.5 will result
    // in being colored (the step function will return a 1.0).
    //
    // You can change the thickness of the grid lines by separating the edge parameter and the 
    // arbitrary subtraction of the `fract` function. This is done for both the x-axis and 
    // the y-axis and the results are then added together.
    //
    // the final result is clamped between 0.0 and 1.0 so as not to create overlay.
    // a value of 1.0 determines that this instance pixel *should* be colored, and
    // 0.0 says otherwise.
    //
    float grid = clamp(
       				 step(0.5, abs(fract(st.x * GRID) - 0.43))
             	   + step(0.5, abs(fract(st.y * GRID) - 0.43)),
        		0.0, 1.0);
    
    // the grid is multiplied by an arbitrary value of 0.2 to decrease it's brightness
    grid *= 0.2;
    
    // The current instance pixel is given values for it's contribution to both the
    // x and the y axes. this is done by absoluting the normalzied coordinates of the
    // pixel and using the step function to determine whether it lies on the respective
    // axis or not.
    //
    float x_axis = step(0.01, abs(st.x));
    float y_axis = step(0.01, abs(st.y));
    
    // a 3-component vector to represent the final color of the graph is created
    //
	// First the color is mixed between white and the grid color value (casted into a vec3)
    // By the amount of `x_axis` (to draw the actual x-axis)
    //
    // The same is done for the y-axis using the previous color value from the x-axis
    //
    // And finally the previous color of the graph is mixed with the actual GRAPH_COLOR
    // mixed by the amount returned by the `plot` function for this specific pixel coordinate
    // effectively drawing the graph.
    //
    vec3 color = mix(vec3(1.0), vec3(grid), x_axis);
   		 color = mix(vec3(1.0), color, y_axis);
   		 color = mix(GRAPH_COLOR, color, 1.0 - plot(st));    
    
    // The output colored is sent to the `gl_FragColor` predefined glsl variable.
    //
    // NOTE: this is deprecated in native OpenGL. I am using the Compatability profile
    // of OpenGL
    gl_FragColor = vec4(color, 1.0);
    
}