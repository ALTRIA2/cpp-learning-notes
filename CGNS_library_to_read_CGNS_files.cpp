##以下是使用CGNS库读取CGNS格式文件的基本示例程序：
#include <stdio.h>
#include <stdlib.h>
#include "cgnslib.h"

int main()
{
    int index_file;
    int index_base;
    int index_zone;
    int index_coord;
    int index_conn;
    int index_field;
    int num_coord;
    int num_conn;
    int num_field;
    int i,j,k;

    float *coord_x, *coord_y, *coord_z;
    int *conn;

    char filename[] = "example.cgns";

    /* 打开CGNS文件 */
    cg_open(filename, CG_MODE_READ, &index_file);

    /* 读取基本信息 */
    cg_base_read(index_file, 1, "Flow", &num_dim, &num_base);

    /* 读取网格信息 */
    cg_zone_read(index_file, 1, 1, "Zone1", &num_vertex, &num_cell, &num_bc);

    /* 读取节点坐标 */
    coord_x = (float*) malloc(num_vertex * sizeof(float));
    coord_y = (float*) malloc(num_vertex * sizeof(float));
    coord_z = (float*) malloc(num_vertex * sizeof(float));
    cg_coord_read(index_file, 1, 1, "CoordinateX", RealSingle, &index_coord, coord_x);
    cg_coord_read(index_file, 1, 1, "CoordinateY", RealSingle, &index_coord, coord_y);
    cg_coord_read(index_file, 1, 1, "CoordinateZ", RealSingle, &index_coord, coord_z);

    /* 读取单元连接信息 */
    conn = (int*) malloc(num_cell * 4 * sizeof(int));
    cg_conn_read(index_file, 1, 1, "Element", Integer, &index_conn, conn);

    /* 读取计算结果数据 */
    cg_nfields(index_file, 1, 1, &num_field);
    for (i = 1; i <= num_field; i++) {
        char fieldname[32];
        DataType_t datatype;
        cg_field_info(index_file, 1, 1, i, &datatype, fieldname);
        float *data = (float*) malloc(num_vertex * sizeof(float));
        cg_field_read(index_file, 1, 1, fieldname, RealSingle, &index_field, data);
        // 处理计算结果数据
        free(data);
    }

    /* 关闭CGNS文件 */
    cg_close(index_file);

    /* 进行进一步的处理和分析 */
    for (i = 0; i < num_vertex; i++) {
        printf("coord_x[%d] = %f, coord_y[%d] = %f, coord_z[%d] = %f\n", i, coord_x[i], i, coord_y[i], i, coord_z[i]);
    }
    for (i = 0; i < num_cell; i++) {
        printf("conn[%d]: %d, %d, %d, %d\n", i, conn[4*i], conn[4*i+1], conn[4*i+2], conn[4*i+3]);
    }

    /* 释放内存 */
    free(coord_x);
    free(coord_y);
    free(coord_z);
    free(conn);

    return 0;
}
#该程序使用CGNS库读取了一个CGNS格式的文件，并获取了其中的网格信息、节点坐标、单元连接信息和计算结果数据。读取完成后，程序可以进行进一步的处理和分析，如输出节点坐标和单元连接信息等。需要注意的是，该程序仅为示例程序，实际应用中需要根据具体问题进行修改和优化。
