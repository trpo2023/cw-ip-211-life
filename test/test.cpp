#include <ctest.h>

#include <Field.hpp>
#include <input.hpp>
#include <logics.hpp>

Field field = {9, 9};

void create_field()
{
    bool map[9][9]
            = {{0, 1, 0, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {0, 1, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 1, 1, 1, 0},
               {0, 0, 0, 0, 0, 1, 0, 1, 0},
               {0, 0, 0, 0, 0, 1, 1, 1, 0}};
    allocate_memory_for_field(field);
    for (int i = 0; i < field.sizeY; i++) {
        for (int k = 0; k < field.sizeX; k++) {
            field.field[i][k] = map[i][k];
        }
    }
}

CTEST(logic, createmap)
{
    create_field();
}

CTEST(logic, countlivecell)
{
    ASSERT_EQUAL(8, counting_live_cells(field, 7, 6));
    ASSERT_EQUAL(2, counting_live_cells(field, 2, 2));
    ASSERT_EQUAL(2, counting_live_cells(field, 5, 5));
    ASSERT_EQUAL(0, counting_live_cells(field, 0, 8));
    ASSERT_EQUAL(2, counting_live_cells(field, 0, 0));
}

CTEST(logic, changemap)
{
    int res[9][9]
            = {{0, 1, 0, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 1, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {0, 1, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 1, 0, 0},
               {0, 0, 0, 0, 0, 1, 0, 1, 0},
               {0, 0, 0, 0, 1, 0, 0, 0, 1},
               {0, 0, 0, 0, 0, 1, 0, 1, 0}};
    change_state(field);
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            ASSERT_EQUAL(res[i][k], field.field[i][k]);
        }
    }
}