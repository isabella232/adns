/*
 * adnshost.h
 * - useful general-purpose resolver client program, header file
 */
/*
 *  This file is
 *    Copyright (C) 1997-1999 Ian Jackson <ian@davenant.greenend.org.uk>
 *
 *  It is part of adns, which is
 *    Copyright (C) 1997-1999 Ian Jackson <ian@davenant.greenend.org.uk>
 *    Copyright (C) 1999 Tony Finch <dot@dotat.at>
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. 
 */

#ifndef ADNSHOST_H_INCLUDED
#define ADNSHOST_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <assert.h>

#include "config.h"
#include "adns.h"
#include "dlist.h"

/* declarations related to option processing */

struct optioninfo;
typedef void optfunc(const struct optioninfo *oi, const char *arg);

struct optioninfo {
  enum oi_type {
    ot_end, ot_desconly,
    ot_flag, ot_value, ot_func, ot_funcarg
  } type;
  const char *desc;
  const char *sopt, *lopt;
  int *storep, value;
  optfunc *func;
  const char *argdesc;
};

enum ttlmode { tm_none, tm_rel, tm_abs };

struct perqueryflags_remember {
  int show_owner, show_type, show_cname;
  int ttl;
};

extern int ov_env, ov_pipe, ov_asynch;
extern int ov_verbose;
extern adns_rrtype ov_type;
extern int ov_search, ov_qc_query, ov_qc_anshost, ov_qc_cname;
extern int ov_tcp, ov_cname;
extern char *ov_id;
extern struct perqueryflags_remember ov_pqfr;

extern optfunc of_help, of_type, of_asynch_id, of_cancel_id;

const struct optioninfo *opt_findl(const char *opt);
const struct optioninfo *opt_finds(const char **optp);
void opt_do(const struct optioninfo *oip, const char *arg);

/* declarations related to query processing */

extern adns_state ads;

void domain_do(const char *domain);

void of_asynch_id(const struct optioninfo *oi, const char *arg);
void of_cancel_id(const struct optioninfo *oi, const char *arg);

/* declarations related to main program and useful utility functions */

void sysfail(const char *what, int errnoval) NONRETURNING;
void usageerr(const char *what, ...) NONRETURNPRINTFFORMAT(1,2);

void *xmalloc(size_t sz);
char *xstrsave(const char *str);

#endif
