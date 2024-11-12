if [ "$#" -lt 1 ]; then
  echo "ppcg generated cuda code."
  ppcg --target=cuda test.c
  nvcc -o test test_host.cu test_kernel.cu
  ./test
fi

action=$1
if [ "$action" = "--clean" ]; then
  echo "remove cuda code."
  rm *.cu
  rm *.hu
  rm test
fi

 