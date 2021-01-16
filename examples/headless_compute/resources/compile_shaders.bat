echo off
for %%x in (compute.comp) do glslangValidator.exe -V shaders\%%x -o shaders\%%x.spv"
pause