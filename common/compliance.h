/* compliance.h - Definitions for compliance modi
 * Copyright (C) 2017 g10 Code GmbH
 *
 * This file is part of GnuPG.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either
 *
 *   - the GNU Lesser General Public License as published by the Free
 *     Software Foundation; either version 3 of the License, or (at
 *     your option) any later version.
 *
 * or
 *
 *   - the GNU General Public License as published by the Free
 *     Software Foundation; either version 2 of the License, or (at
 *     your option) any later version.
 *
 * or both in parallel, as here.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GNUPG_COMMON_COMPLIANCE_H
#define GNUPG_COMMON_COMPLIANCE_H

#include <gcrypt.h>
#include "openpgpdefs.h"

enum gnupg_compliance_mode
  {
    CO_GNUPG, CO_RFC4880, CO_RFC2440,
    CO_PGP6, CO_PGP7, CO_PGP8, CO_DE_VS
  };

int gnupg_pk_is_compliant (enum gnupg_compliance_mode compliance, int algo,
                           gcry_mpi_t key[], unsigned int keylength,
                           const char *curvename);
int gnupg_cipher_is_compliant (enum gnupg_compliance_mode compliance,
                               cipher_algo_t cipher);
int gnupg_digest_is_compliant (enum gnupg_compliance_mode compliance,
                               digest_algo_t digest);
const char *gnupg_status_compliance_flag (enum gnupg_compliance_mode compliance);

#endif /*GNUPG_COMMON_COMPLIANCE_H*/
