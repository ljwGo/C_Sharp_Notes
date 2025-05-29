#version 460 core

// Name and type need to be the same.
in vec3 inVColor;
out vec4 FragColor;
// global variable
uniform float alpha;

void main(){
  // global variable gl_FragColor is removed after version 420
  // gl_FragColor = vec4(inVColor, alpha);
  FragColor = vec4(inVColor * alpha, 1.0);
  // FragColor = vec4(inVColor, alpha);
}