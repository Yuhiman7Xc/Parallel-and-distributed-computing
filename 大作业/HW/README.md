# Floyd算法使用串行，MPI，OpenMP实现的对比

## 实验环境

    Ubuntu 18

- Data.cpp：数据生成函数，默认生成3000*3000的随机邻接矩阵，矩阵元素为0到100的整数，代表输入的图。
- Floyd.cpp：串行实现Floyd算法
- MPI_Floyd.cpp：利用MPI并行实现Floyd算法
- OpenMP_Floyd.cpp：利用OpenMP并行实现Floyd算法