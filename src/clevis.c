/* vim: set tabstop=8 shiftwidth=4 softtabstop=4 expandtab smarttab colorcolumn=80: */
/*
 * Copyright (c) 2015 Red Hat, Inc.
 * Author: Nathaniel McCallum <npmccallum@redhat.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    char path[PATH_MAX] = {};
    char *args[argc];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s COMMAND ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (readlink("/proc/self/exe", path, sizeof(path) - 1) < 0)
        return EXIT_FAILURE;

    if (strlen(path) + strlen(argv[1]) + 2 > sizeof(path))
        return EXIT_FAILURE;

    strcat(path, "-");
    strcat(path, argv[1]);

    args[0] = path;
    for (int i = 2; i < argc; i++)
        args[i - 1] = argv[i];
    args[argc - 1] = NULL;

    execv(path, args);
    return EXIT_FAILURE;
}
