echo off
for %%x in (suzanne.vert suzanne.frag) do glslangValidator.exe -V shaders\%%x -o shaders\%%x.spv"
pause