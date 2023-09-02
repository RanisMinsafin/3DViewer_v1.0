#include <check.h>

#include "backend/parser.h"

START_TEST(test_parser_data_1) {
  Data data = openFile("./models/cube.obj");

  Data ref;
  ref.countOfVertices = 8;
  ref.countOfFacets = 72;
  ref.status = OK;
  ref.countV = 8;
  ref.matrix.rows = 8;
  ref.matrix.columns = 3;
  double m = 0;
  ref.matrix.m = &m;

  ref.facets.countOfVertiсesInFacets = 72;
  int vertices = 1;
  ref.facets.vertices = &vertices;

  ck_assert_int_eq(data.countOfVertices, ref.countOfVertices);
  ck_assert_int_eq(data.countOfFacets, ref.countOfFacets);
  ck_assert_int_eq(data.status, ref.status);
  ck_assert_int_eq(data.countV, ref.countV);
  ck_assert_int_eq(data.matrix.rows, ref.matrix.rows);
  ck_assert_int_eq(data.matrix.columns, ref.matrix.columns);
  ck_assert_double_eq(*(data.matrix.m), *(ref.matrix.m));
  ck_assert_int_eq(data.facets.countOfVertiсesInFacets,
                   ref.facets.countOfVertiсesInFacets);
  ck_assert_int_eq(*(data.facets.vertices), *(ref.facets.vertices));
  if (data.matrix.m) free(data.matrix.m);
  if (data.facets.vertices) free(data.facets.vertices);
}
END_TEST

START_TEST(test_afine_1) {
  Data data = openFile("./models/Pyramid.obj");

  Data ref;
  ref.countOfVertices = 6;
  ref.countOfFacets = 48;
  ref.status = OK;
  ref.countV = 6;
  ref.matrix.rows = 6;
  ref.matrix.columns = 3;
  double m = 0;
  ref.matrix.m = &m;

  ref.facets.countOfVertiсesInFacets = 48;
  int vertices = 1;
  ref.facets.vertices = &vertices;

  moveX(&data, 10);
  moveY(&data, 7);
  moveZ(&data, 15);

  rotateX(&data, 10);
  rotateY(&data, 7);
  rotateZ(&data, 15);

  ck_assert_int_eq(data.countOfVertices, ref.countOfVertices);
  ck_assert_int_eq(data.countOfFacets, ref.countOfFacets);
  ck_assert_int_eq(data.status, ref.status);
  ck_assert_int_eq(data.countV, ref.countV);
  ck_assert_int_eq(data.matrix.rows, ref.matrix.rows);
  ck_assert_int_eq(data.matrix.columns, ref.matrix.columns);
  ck_assert_double_eq(*(data.matrix.m), *(ref.matrix.m));
  ck_assert_int_eq(data.facets.countOfVertiсesInFacets,
                   ref.facets.countOfVertiсesInFacets);
  ck_assert_int_eq(*(data.facets.vertices), *(ref.facets.vertices));
  if (data.matrix.m) free(data.matrix.m);
  if (data.facets.vertices) free(data.facets.vertices);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_parser_data_1);
  tcase_add_test(tc1_1, test_afine_1);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return (0);
}