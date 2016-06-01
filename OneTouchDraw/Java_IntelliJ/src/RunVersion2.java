import java.util.Stack;

/**
 * Created by LeadroyaL on 2016/5/19 .
 * version2 add weight
 * add calc length
 */
public class RunVersion2 {

    private Stack<Integer> stack = new Stack<>();
    private int currentPoint;
    private int beforeLength, afterLength, deltaLength;
    private int size;
    private int length;
    private int[] sectionLength;
    private int sectionOffset;
    private int[] route;
    private int routeOffset;
    private int[][] tmp_mat;

    //exp1
//    private int[][] mat = {
//            {0, 0, 0, 0, 0, 0, 0, 1, 1},
//            {0, 0, 0, 0, 1, 0, 1, 0, 0},
//            {0, 0, 0, 1, 0, 1, 0, 0, 0},
//            {0, 0, 1, 0, 0, 1, 0, 1, 0},
//            {0, 1, 0, 0, 0, 0, 1, 0, 1},
//            {0, 0, 1, 1, 0, 0, 0, 0, 0},
//            {0, 1, 0, 0, 1, 0, 0, 0, 0},
//            {1, 0, 0, 1, 0, 0, 0, 0, 0},
//            {1, 0, 0, 0, 1, 0, 0, 0, 0}
//    };
    //exp2
    private int[][] mat = {
            {0, 2, 2, 1, 1, 1, 1, 1, 1},
            {2, 0, 1, 1, 1, 1, 1, 1, 1},
            {2, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
    };

    RunVersion2() {
        print("run");
        int code = start_here();
        // -1 is cannot
        // 0 is success
        print(code);
    }

    private int start_here() {
        size = mat.length;
        init_tp_mat();
        if (!check_connect()) {
            print("Not Connect");
            return -1;
        }
        int odd = calc_odd();
        if (odd != 2 && odd != 0) {
            print("Not odd");
            return -1;
        }
        print("Calculate Length");
        length = calc_length();
        sectionLength = new int[length];
        route = new int[length];
        print("Start Calculate");
        if (odd == 0)
            currentPoint = (int) (Math.random() * size);

        stack.push(currentPoint);
        sectionOffset = 0;
        routeOffset = 0;
        sectionLength[sectionOffset] = 1;
        while (true) {
            currentPoint = stack.pop();
            add_to_route();
            if (check_finish()) break;
            beforeLength = stack.size();
            for (int i = 0; i < size; i++) {
                if (check_next(currentPoint, i))
                    stack.push(i);
            }
            afterLength = stack.size();
            deltaLength = afterLength - beforeLength;
            if (deltaLength == 0) {
                reverse();
            } else {
                add_to_section();
            }

            if (Math.random() > 1)
                break;
        }
        for (int i = 0; i < routeOffset; i++) {
            System.out.print(route[i] + " ");
        }
        print("");
        print("End Calculate");
        return 0;
    }

    private void init_tp_mat() {
        tmp_mat = new int[size][size];
        for (int i = 0; i < size; i++) {
            System.arraycopy(mat[i], 0, tmp_mat[i], 0, size);
        }
    }

    private int calc_length() {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sum += mat[i][j];
            }
        }
        return sum / 2 + 1;
    }

    private void add_to_section() {
        sectionOffset++;
        sectionLength[sectionOffset - 1]--;
        sectionLength[sectionOffset] = deltaLength;
    }

    private void add_to_route() {
        route[routeOffset] = currentPoint;
        if (routeOffset == 0) {
            routeOffset++;
            return;
        }
        mat[route[routeOffset]][route[routeOffset - 1]]--;
        mat[route[routeOffset - 1]][route[routeOffset]]--;
        routeOffset++;
    }

    private void reverse() {
        routeOffset--;
        mat[route[routeOffset]][route[routeOffset - 1]]++;
        mat[route[routeOffset - 1]][route[routeOffset]]++;
        //then adjust section
        sectionLength[sectionOffset]--;
        while (sectionLength[sectionOffset] == 0) {
            //then reverse mat
            routeOffset--;
            sectionOffset--;
            mat[route[routeOffset]][route[routeOffset - 1]]++;
            mat[route[routeOffset - 1]][route[routeOffset]]++;
        }
    }

    private boolean check_finish() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (mat[i][j] != 0)
                    return false;
            }
        }
        return true;
    }

    private boolean check_next(int currentPoint, int i) {
        return mat[currentPoint][i] > 0;
    }

    private int calc_odd() {
        int odd = 0;
        int sum;
        for (int i = 0; i < size; i++) {
            sum = 0;
            for (int j = 0; j < size; j++) {
                sum += mat[i][j];
            }
            if (sum % 2 != 0) {
                odd += 1;
                currentPoint = i;
            }
        }
        return odd;
    }

    private boolean check_connect() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (tmp_mat[i][j] != tmp_mat[j][i])
                    print("INPUT ERROR");
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (tmp_mat[i][j] != 0) {
                    for (int k = 0; k < size; k++) {
                        if (tmp_mat[k][i] != 0)
                            tmp_mat[k][j] = tmp_mat[j][k] = 1;
                    }
                }
            }
        }
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (tmp_mat[i][j] == 0)
                    return false;
        return true;
    }

    private void print(Object s) {
        System.out.println(s);
    }
}
