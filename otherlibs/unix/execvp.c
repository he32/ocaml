/**************************************************************************/
/*                                                                        */
/*                                 OCaml                                  */
/*                                                                        */
/*             Xavier Leroy, projet Cristal, INRIA Rocquencourt           */
/*                                                                        */
/*   Copyright 1996 Institut National de Recherche en Informatique et     */
/*     en Automatique.                                                    */
/*                                                                        */
/*   All rights reserved.  This file is distributed under the terms of    */
/*   the GNU Lesser General Public License version 2.1, with the          */
/*   special exception on linking described in the file LICENSE.          */
/*                                                                        */
/**************************************************************************/

#include <caml/mlvalues.h>
#include <caml/memory.h>
#define CAML_INTERNALS
#include <caml/osdeps.h>
#include "unixsupport.h"

CAMLprim value unix_execvp(value path, value args)
{
  char_os ** argv;
  char_os * wpath;
  caml_unix_check_path(path, "execvp");
  argv = cstringvect(args, "execvp");
  wpath = caml_stat_strdup_to_os(String_val(path));
  (void) execvp_os((const char_os *)wpath, EXECV_CAST argv);
  caml_stat_free(wpath);
  cstringvect_free(argv);
  uerror("execvp", path);
  return Val_unit;                  /* never reached, but suppress warnings */
                                    /* from smart compilers */
}

CAMLprim value unix_execvpe(value path, value args, value env)
{
  char_os * exefile, * wpath;
  char_os ** argv;
  char_os ** envp;
  caml_unix_check_path(path, "execvpe");
  wpath = caml_stat_strdup_to_os(String_val(path));
  exefile = caml_search_exe_in_path(wpath);
  caml_stat_free(wpath);
  argv = cstringvect(args, "execvpe");
  envp = cstringvect(env, "execvpe");
  (void) execve_os((const char_os *)exefile, EXECV_CAST argv, EXECV_CAST envp);
  caml_stat_free(exefile);
  cstringvect_free(argv);
  cstringvect_free(envp);
  uerror("execvpe", path);
  return Val_unit;                  /* never reached, but suppress warnings */
                                    /* from smart compilers */
}
