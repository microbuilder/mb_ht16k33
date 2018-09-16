/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

 /**
  * @file
  * @brief Shell commands for the 'clr' command..
  */

#include "os/mynewt.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "console/console.h"
#include "ht16k33/ht16k33.h"
#include "ht16k33_priv.h"

#if MYNEWT_VAL(HT16K33_CLI)

/* These need to be masked out for unit tests to run */
#include "shell/shell.h"
#include "parse/parse.h"

static int ht16k33_shell_cmd(int argc, char **argv);

static struct shell_cmd ht16k33_shell_cmd_struct = {
    .sc_cmd = "ht16k33",
    .sc_cmd_func = ht16k33_shell_cmd
};

#if 0
static int
ht16k33_shell_err_too_many_args(char *cmd_name)
{
    console_printf("Error: too many arguments for command \"%s\"\n",
                   cmd_name);
    return EINVAL;
}
#endif

#if 0
static int
ht16k33_shell_err_missing_arg(char *arg_name)
{
    console_printf("Error: missing arg [%s]\n",
                   arg_name);
    return EINVAL;
}
#endif

static int
ht16k33_shell_err_unknown_arg(char *cmd_name)
{
    console_printf("Error: unknown argument \"%s\"\n",
                   cmd_name);
    return EINVAL;
}

static int
ht16k33_shell_help(void)
{
    console_printf("%s cmd [params...]\n", ht16k33_shell_cmd_struct.sc_cmd);
    console_printf("cmd:\n");
    console_printf("  todo    todo description\n");

    return 0;
}

static int
ht16k33_shell_todo_help(void)
{
    console_printf("%s todo cmd [params...]\n", ht16k33_shell_cmd_struct.sc_cmd);
    console_printf("cmd:\n");
    console_printf("  todo <one> <two>      todo description\n");

    return 0;
}

static int
ht16k33_shell_todo(int argc, char **argv)
{
    if (argc == 2) {
        return ht16k33_shell_todo_help();
    }

#if 0
    /* cct2XYZ */
    if (argc > 2 && strcmp(argv[2], "cct2XYZ") == 0) {
        return clr_shell_conv_cct_XYZ(argc, argv);
    }
#endif

    /* XYZ2cct */
    return ht16k33_shell_err_unknown_arg(argv[2]);
}

static int
ht16k33_shell_cmd(int argc, char **argv)
{
    if (argc == 1) {
        return ht16k33_shell_help();
    }

    /* 'todo' sub-command */
    if (argc > 1 && strcmp(argv[1], "todo") == 0) {
        return ht16k33_shell_todo(argc, argv);
    }

    return ht16k33_shell_err_unknown_arg(argv[1]);
}

int
ht16k33_shell_init(void)
{
    int rc;

    rc = shell_cmd_register(&ht16k33_shell_cmd_struct);
    SYSINIT_PANIC_ASSERT(rc == 0);

    return rc;
}

#endif /* HT16K33_CLI */
