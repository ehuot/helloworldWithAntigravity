#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Programme de tests unitaires pour l'executable hello.
 * Conforme a la norme ANSI C (C89 / C90).
 */

/*
 * Compare deux fichiers octet par octet.
 * Retourne 1 si identiques, 0 sinon.
 */
static int compare_files(const char *file1, const char *file2)
{
    FILE *f1;
    FILE *f2;
    int c1, c2;

    f1 = fopen(file1, "r");
    if (!f1) {
        perror(file1);
        return 0;
    }

    f2 = fopen(file2, "r");
    if (!f2) {
        perror(file2);
        fclose(f1);
        return 0;
    }

    do {
        c1 = fgetc(f1);
        c2 = fgetc(f2);
        if (c1 != c2) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    } while (c1 != EOF && c2 != EOF);

    fclose(f1);
    fclose(f2);
    return (c1 == EOF && c2 == EOF);
}

/*
 * Execute une commande en redirigeant sa sortie vers un fichier temporaire,
 * puis compare avec le fichier attendu.
 */
static int run_test(const char *test_name, const char *command, const char *expected_file)
{
    char full_cmd[256];
    const char *tmp_file = "test_output.tmp";
    int ret;
    int success;

    sprintf(full_cmd, "%s > %s", command, tmp_file);
    ret = system(full_cmd);
    if (ret != 0) {
        printf("[FAIL] %s: la commande '%s' a echoue (code %d)\n", test_name, command, ret);
        remove(tmp_file);
        return 0;
    }

    success = compare_files(tmp_file, expected_file);
    if (success) {
        printf("[PASS] %s: succes (%s == %s)\n", test_name, command, expected_file);
    } else {
        printf("[FAIL] %s: la sortie de '%s' ne correspond pas a '%s'\n", test_name, command, expected_file);
    }

    remove(tmp_file);
    return success;
}

/*
 * Teste le comportement par defaut sans argument (attendu : 5 repetitions).
 */
static int test_default(void)
{
    const char *cmd = "./hello > test_default.tmp";
    FILE *f;
    int count = 0;
    char line[128];
    int ret;

    ret = system(cmd);
    if (ret != 0) {
        printf("[FAIL] Test 4 (sans argument): la commande a echoue\n");
        remove("test_default.tmp");
        return 0;
    }

    f = fopen("test_default.tmp", "r");
    if (!f) {
        perror("test_default.tmp");
        return 0;
    }

    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "Hello World\n") == 0) {
            count++;
        }
    }
    fclose(f);
    remove("test_default.tmp");

    if (count == 5) {
        printf("[PASS] Test 4 (sans argument): 5 repetitions de \"Hello World\" detectees (defaut)\n");
        return 1;
    } else {
        printf("[FAIL] Test 4 (sans argument): attendu 5 repetitions, obtenu %d\n", count);
        return 0;
    }
}

int main(void)
{
    int total = 0;
    int passed = 0;

    printf("=========================================\n");
    printf("   Execution des tests unitaires (hello) \n");
    printf("=========================================\n\n");

    /* Test 1 : 1 iteration */
    total++;
    if (run_test("Test 1 (1 iteration)", "./hello 1", "helloworld1.txt")) {
        passed++;
    }

    /* Test 2 : 2 iterations */
    total++;
    if (run_test("Test 2 (2 iterations)", "./hello 2", "helloworld2.txt")) {
        passed++;
    }

    /* Test 3 : 3 iterations */
    total++;
    if (run_test("Test 3 (3 iterations)", "./hello 3", "helloworld3.txt")) {
        passed++;
    }

    /* Test 4 : sans argument (valeur par defaut = 5) */
    total++;
    if (test_default()) {
        passed++;
    }

    printf("\n=========================================\n");
    printf("   Bilan : %d/%d test(s) reussi(s)\n", passed, total);
    printf("=========================================\n");

    return (passed == total) ? 0 : 1;
}
