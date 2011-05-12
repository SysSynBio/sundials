/*
 * -----------------------------------------------------------------
 * $Revision: 1.5 $
 * $Date: 2007/07/05 19:10:36 $
 * ----------------------------------------------------------------- 
 * Programmer(s): Alan C. Hindmarsh and Radu Serban @ LLNL
 * -----------------------------------------------------------------
 * Copyright (c) 2002, The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see the LICENSE file.
 * -----------------------------------------------------------------
 * This is the header file (private version) for the IDABBDPRE
 * module, for a band-block-diagonal preconditioner, i.e. a
 * block-diagonal matrix with banded blocks, for use with IDAS
 * and an IDASPILS linear solver.
 * -----------------------------------------------------------------
 */

#ifndef _IDASBBDPRE_IMPL_H
#define _IDASBBDPRE_IMPL_H

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

#include <idas/idas_bbdpre.h>
#include <sundials/sundials_band.h>

/*
 * -----------------------------------------------------------------
 * Definition of IBBDPrecData
 * -----------------------------------------------------------------
 */

typedef struct IBBDPrecDataRec {

  /* passed by user to IDABBDPrecAlloc and used by
     IDABBDPrecSetup/IDABBDPrecSolve functions */

  int mudq, mldq, mukeep, mlkeep;
  realtype rel_yy;
  IDABBDLocalFn glocal;
  IDABBDCommFn gcomm;

  /* allocated for use by IDABBDPrecSetup */

  N_Vector tempv4;

  /* set by IDABBDPrecon and used by IDABBDPrecSolve */

  DlsMat PP;
  int *pivots;

  /* set by IDABBDPrecAlloc and used by IDABBDPrecSetup */

  int n_local;

  /* available for optional output */

  long int rpwsize;
  long int ipwsize;
  long int nge;

  /* pointer to ida_mem */

  void *ida_mem;

} *IBBDPrecData;

/*
 * -----------------------------------------------------------------
 * Type: IDABBDPrecDataB
 * -----------------------------------------------------------------
 */

typedef struct IDABBDPrecDataRecB{

  /* BBD user functions (glocB and cfnB) for backward run */
  IDABBDLocalFnB glocalB;
  IDABBDCommFnB  gcommB;
    
  /* BBD prec data */
  /* //!void *bbd_dataB; */

} *IDABBDPrecDataB;


/*
 * -----------------------------------------------------------------
 * IDABBDPRE error messages
 * -----------------------------------------------------------------
 */

#define MSGBBD_MEM_NULL    "Integrator memory is NULL."
#define MSGBBD_LMEM_NULL   "Linear solver memory is NULL. One of the SPILS linear solvers must be attached."
#define MSGBBD_MEM_FAIL    "A memory request failed."
#define MSGBBD_BAD_NVECTOR "A required vector operation is not implemented."
#define MSGBBD_PMEM_NULL   "BBD peconditioner memory is NULL. IDABBDPrecInit must be called."
#define MSGBBD_FUNC_FAILED "The Glocal or Gcomm routine failed in an unrecoverable manner."

#define MSGBBD_AMEM_NULL   "idaadj_mem = NULL illegal."
#define MSGBBD_PDATAB_NULL "IDABBDPRE memory is NULL for the backward integration."
#define MSGBBD_BAD_T       "Bad t for interpolation."

#ifdef __cplusplus
}
#endif

#endif