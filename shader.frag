#version 150

uniform float time;
uniform vec2 resolution;
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;

in vec2 texCoordVarying;
out vec4 outputColor;

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);

  float r = texture(tex2, texCoordVarying).r;
  float g = texture(tex1, texCoordVarying).g;
  float b = texture(tex0, texCoordVarying).b;

  outputColor = vec4(r, g, b, 1.0);
}
