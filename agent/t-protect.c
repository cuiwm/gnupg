/* t-protect.c - Module tests for protect.c
 * Copyright (C) 2005 Free Software Foundation, Inc.
 *
 * This file is part of GnuPG.
 *
 * GnuPG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * GnuPG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "agent.h"


#define pass()  do { ; } while(0)
#define fail()  do { fprintf (stderr, "%s:%d: test failed\n",\
                              __FILE__,__LINE__);            \
                     exit (1);                               \
                   } while(0)


static void
test_agent_protect (void)
{
  /* Protect the key encoded in canonical format in PLAINKEY.  We assume
     a valid S-Exp here. */

  unsigned int i;
  int ret;
  struct key_spec
  {
    const char *string;
  };
  /* Valid RSA key.  */
  struct key_spec key_rsa_valid =
    {
      "\x28\x31\x31\x3A\x70\x72\x69\x76\x61\x74\x65\x2D\x6B\x65\x79\x28\x33\x3A\x72\x73"
      "\x61\x28\x31\x3A\x6E\x31\x32\x39\x3A\x00\xB6\xB5\x09\x59\x6A\x9E\xCA\xBC\x93\x92"
      "\x12\xF8\x91\xE6\x56\xA6\x26\xBA\x07\xDA\x85\x21\xA9\xCA\xD4\xC0\x8E\x64\x0C\x04"
      "\x05\x2F\xBB\x87\xF4\x24\xEF\x1A\x02\x75\xA4\x8A\x92\x99\xAC\x9D\xB6\x9A\xBE\x3D"
      "\x01\x24\xE6\xC7\x56\xB1\xF7\xDF\xB9\xB8\x42\xD6\x25\x1A\xEA\x6E\xE8\x53\x90\x49"
      "\x5C\xAD\xA7\x3D\x67\x15\x37\xFC\xE5\x85\x0A\x93\x2F\x32\xBA\xB6\x0A\xB1\xAC\x1F"
      "\x85\x2C\x1F\x83\xC6\x25\xE7\xA7\xD7\x0C\xDA\x9E\xF1\x6D\x5C\x8E\x47\x73\x9D\x77"
      "\xDF\x59\x26\x1A\xBE\x84\x54\x80\x7F\xF4\x41\xE1\x43\xFB\xD3\x7F\x85\x45\x29\x28"
      "\x31\x3A\x65\x33\x3A\x01\x00\x01\x29\x28\x31\x3A\x64\x31\x32\x38\x3A\x07\x7A\xD3"
      "\xDE\x28\x42\x45\xF4\x80\x6A\x1B\x82\xB7\x9E\x61\x6F\xBD\xE8\x21\xC8\x2D\x69\x1A"
      "\x65\x66\x5E\x57\xB5\xFA\xD3\xF3\x4E\x67\xF4\x01\xE7\xBD\x2E\x28\x69\x9E\x89\xD9"
      "\xC4\x96\xCF\x82\x19\x45\xAE\x83\xAC\x7A\x12\x31\x17\x6A\x19\x6B\xA6\x02\x7E\x77"
      "\xD8\x57\x89\x05\x5D\x50\x40\x4A\x7A\x2A\x95\xB1\x51\x2F\x91\xF1\x90\xBB\xAE\xF7"
      "\x30\xED\x55\x0D\x22\x7D\x51\x2F\x89\xC0\xCD\xB3\x1A\xC0\x6F\xA9\xA1\x95\x03\xDD"
      "\xF6\xB6\x6D\x0B\x42\xB9\x69\x1B\xFD\x61\x40\xEC\x17\x20\xFF\xC4\x8A\xE0\x0C\x34"
      "\x79\x6D\xC8\x99\xE5\x29\x28\x31\x3A\x70\x36\x35\x3A\x00\xD5\x86\xC7\x8E\x5F\x1B"
      "\x4B\xF2\xE7\xCD\x7A\x04\xCA\x09\x19\x11\x70\x6F\x19\x78\x8B\x93\xE4\x4E\xE2\x0A"
      "\xAF\x46\x2E\x83\x63\xE9\x8A\x72\x25\x3E\xD8\x45\xCC\xBF\x24\x81\xBB\x35\x1E\x85"
      "\x57\xC8\x5B\xCF\xFF\x0D\xAB\xDB\xFF\x8E\x26\xA7\x9A\x09\x38\x09\x6F\x27\x29\x28"
      "\x31\x3A\x71\x36\x35\x3A\x00\xDB\x0C\xDF\x60\xF2\x6F\x2A\x29\x6C\x88\xD6\xBF\x9F"
      "\x8E\x5B\xE4\x5C\x0D\xDD\x71\x3C\x96\xCC\x73\xEB\xCB\x48\xB0\x61\x74\x09\x43\xF2"
      "\x1D\x2A\x93\xD6\xE4\x2A\x72\x11\xE7\xF0\x2A\x95\xDC\xED\x6C\x39\x0A\x67\xAD\x21"
      "\xEC\xF7\x39\xAE\x8A\x0C\xA4\x6F\xF2\xEB\xB3\x29\x28\x31\x3A\x75\x36\x34\x3A\x33"
      "\x14\x91\x95\xF1\x69\x12\xDB\x20\xA4\x8D\x02\x0D\xBC\x3B\x9E\x38\x81\xB3\x9D\x72"
      "\x2B\xF7\x93\x78\xF6\x34\x0F\x43\x14\x8A\x6E\x9F\xC5\xF5\x3E\x28\x53\xB7\x38\x7B"
      "\xA4\x44\x3B\xA5\x3A\x52\xFC\xA8\x17\x3D\xE6\xE8\x5B\x42\xF9\x78\x3D\x4A\x78\x17"
      "\xD0\x68\x0B\x29\x29\x29\x00"
    };
  /* This RSA key is missing the last closing brace.  */
  struct key_spec key_rsa_bogus_0 =
    {
      "\x28\x31\x31\x3A\x70\x72\x69\x76\x61\x74\x65\x2D\x6B\x65\x79\x28\x33\x3A\x72\x73"
      "\x61\x28\x31\x3A\x6E\x31\x32\x39\x3A\x00\xB6\xB5\x09\x59\x6A\x9E\xCA\xBC\x93\x92"
      "\x12\xF8\x91\xE6\x56\xA6\x26\xBA\x07\xDA\x85\x21\xA9\xCA\xD4\xC0\x8E\x64\x0C\x04"
      "\x05\x2F\xBB\x87\xF4\x24\xEF\x1A\x02\x75\xA4\x8A\x92\x99\xAC\x9D\xB6\x9A\xBE\x3D"
      "\x01\x24\xE6\xC7\x56\xB1\xF7\xDF\xB9\xB8\x42\xD6\x25\x1A\xEA\x6E\xE8\x53\x90\x49"
      "\x5C\xAD\xA7\x3D\x67\x15\x37\xFC\xE5\x85\x0A\x93\x2F\x32\xBA\xB6\x0A\xB1\xAC\x1F"
      "\x85\x2C\x1F\x83\xC6\x25\xE7\xA7\xD7\x0C\xDA\x9E\xF1\x6D\x5C\x8E\x47\x73\x9D\x77"
      "\xDF\x59\x26\x1A\xBE\x84\x54\x80\x7F\xF4\x41\xE1\x43\xFB\xD3\x7F\x85\x45\x29\x28"
      "\x31\x3A\x65\x33\x3A\x01\x00\x01\x29\x28\x31\x3A\x64\x31\x32\x38\x3A\x07\x7A\xD3"
      "\xDE\x28\x42\x45\xF4\x80\x6A\x1B\x82\xB7\x9E\x61\x6F\xBD\xE8\x21\xC8\x2D\x69\x1A"
      "\x65\x66\x5E\x57\xB5\xFA\xD3\xF3\x4E\x67\xF4\x01\xE7\xBD\x2E\x28\x69\x9E\x89\xD9"
      "\xC4\x96\xCF\x82\x19\x45\xAE\x83\xAC\x7A\x12\x31\x17\x6A\x19\x6B\xA6\x02\x7E\x77"
      "\xD8\x57\x89\x05\x5D\x50\x40\x4A\x7A\x2A\x95\xB1\x51\x2F\x91\xF1\x90\xBB\xAE\xF7"
      "\x30\xED\x55\x0D\x22\x7D\x51\x2F\x89\xC0\xCD\xB3\x1A\xC0\x6F\xA9\xA1\x95\x03\xDD"
      "\xF6\xB6\x6D\x0B\x42\xB9\x69\x1B\xFD\x61\x40\xEC\x17\x20\xFF\xC4\x8A\xE0\x0C\x34"
      "\x79\x6D\xC8\x99\xE5\x29\x28\x31\x3A\x70\x36\x35\x3A\x00\xD5\x86\xC7\x8E\x5F\x1B"
      "\x4B\xF2\xE7\xCD\x7A\x04\xCA\x09\x19\x11\x70\x6F\x19\x78\x8B\x93\xE4\x4E\xE2\x0A"
      "\xAF\x46\x2E\x83\x63\xE9\x8A\x72\x25\x3E\xD8\x45\xCC\xBF\x24\x81\xBB\x35\x1E\x85"
      "\x57\xC8\x5B\xCF\xFF\x0D\xAB\xDB\xFF\x8E\x26\xA7\x9A\x09\x38\x09\x6F\x27\x29\x28"
      "\x31\x3A\x71\x36\x35\x3A\x00\xDB\x0C\xDF\x60\xF2\x6F\x2A\x29\x6C\x88\xD6\xBF\x9F"
      "\x8E\x5B\xE4\x5C\x0D\xDD\x71\x3C\x96\xCC\x73\xEB\xCB\x48\xB0\x61\x74\x09\x43\xF2"
      "\x1D\x2A\x93\xD6\xE4\x2A\x72\x11\xE7\xF0\x2A\x95\xDC\xED\x6C\x39\x0A\x67\xAD\x21"
      "\xEC\xF7\x39\xAE\x8A\x0C\xA4\x6F\xF2\xEB\xB3\x29\x28\x31\x3A\x75\x36\x34\x3A\x33"
      "\x14\x91\x95\xF1\x69\x12\xDB\x20\xA4\x8D\x02\x0D\xBC\x3B\x9E\x38\x81\xB3\x9D\x72"
      "\x2B\xF7\x93\x78\xF6\x34\x0F\x43\x14\x8A\x6E\x9F\xC5\xF5\x3E\x28\x53\xB7\x38\x7B"
      "\xA4\x44\x3B\xA5\x3A\x52\xFC\xA8\x17\x3D\xE6\xE8\x5B\x42\xF9\x78\x3D\x4A\x78\x17"
      "\xD0\x68\x0B\x29\x29\x00"
    };
  /* This RSA key is the 'e' value.  */
  struct key_spec key_rsa_bogus_1 =
    {
      "\x28\x31\x31\x3A\x70\x72\x69\x76\x61\x74\x65\x2D\x6B\x65\x79\x28\x33\x3A\x72\x73"
      "\x61\x28\x31\x3A\x6E\x31\x32\x39\x3A\x00\xA8\x80\xB6\x71\xF4\x95\x9F\x49\x84\xED"
      "\xC1\x1D\x5F\xFF\xED\x14\x7B\x9C\x6A\x62\x0B\x7B\xE2\x3E\x41\x48\x49\x85\xF5\x64"
      "\x50\x04\x9D\x30\xFC\x84\x1F\x01\xC3\xC3\x15\x03\x48\x6D\xFE\x59\x0B\xB0\xD0\x3E"
      "\x68\x8A\x05\x7A\x62\xB0\xB9\x6E\xC5\xD2\xA8\xEE\x0C\x6B\xDE\x5E\x3D\x8E\xE8\x8F"
      "\xB3\xAE\x86\x99\x7E\xDE\x2B\xC2\x4D\x60\x51\xDB\xB1\x2C\xD0\x38\xEC\x88\x62\x3E"
      "\xA9\xDD\x11\x53\x04\x17\xE4\xF2\x07\x50\xDC\x44\xED\x14\xF5\x0B\xAB\x9C\xBC\x24"
      "\xC6\xCB\xAD\x0F\x05\x25\x94\xE2\x73\xEB\x14\xD5\xEE\x5E\x18\xF0\x40\x31\x29\x28"
      "\x31\x3A\x64\x31\x32\x38\x3A\x40\xD0\x55\x9D\x2A\xA7\xBC\xBF\xE2\x3E\x33\x98\x71"
      "\x7B\x37\x3D\xB8\x38\x57\xA1\x43\xEA\x90\x81\x42\xCA\x23\xE1\xBF\x9C\xA8\xBC\xC5"
      "\x9B\xF8\x9D\x77\x71\xCD\xD3\x85\x8B\x20\x3A\x92\xE9\xBC\x79\xF3\xF7\xF5\x6D\x15"
      "\xA3\x58\x3F\xC2\xEB\xED\x72\xD4\xE0\xCF\xEC\xB3\xEC\xEB\x09\xEA\x1E\x72\x6A\xBA"
      "\x95\x82\x2C\x7E\x30\x95\x66\x3F\xA8\x2D\x40\x0F\x7A\x12\x4E\xF0\x71\x0F\x97\xDB"
      "\x81\xE4\x39\x6D\x24\x58\xFA\xAB\x3A\x36\x73\x63\x01\x77\x42\xC7\x9A\xEA\x87\xDA"
      "\x93\x8F\x6C\x64\xAD\x9E\xF0\xCA\xA2\x89\xA4\x0E\xB3\x25\x73\x29\x28\x31\x3A\x70"
      "\x36\x35\x3A\x00\xC3\xF7\x37\x3F\x9D\x93\xEC\xC7\x5E\x4C\xB5\x73\x29\x62\x35\x80"
      "\xC6\x7C\x1B\x1E\x68\x5F\x92\x56\x77\x0A\xE2\x8E\x95\x74\x87\xA5\x2F\x83\x2D\xF7"
      "\xA1\xC2\x78\x54\x18\x6E\xDE\x35\xF0\x9F\x7A\xCA\x80\x5C\x83\x5C\x44\xAD\x8B\xE7"
      "\x5B\xE2\x63\x7D\x6A\xC7\x98\x97\x29\x28\x31\x3A\x71\x36\x35\x3A\x00\xDC\x1F\xB1"
      "\xB3\xD8\x13\xE0\x09\x19\xFD\x1C\x58\xA1\x2B\x02\xB4\xC8\xF2\x1C\xE7\xF9\xC6\x3B"
      "\x68\xB9\x72\x43\x86\xEF\xA9\x94\x68\x02\xEF\x7D\x77\xE0\x0A\xD1\xD7\x48\xFD\xCD"
      "\x98\xDA\x13\x8A\x76\x48\xD4\x0F\x63\x28\xFA\x01\x1B\xF3\xC7\x15\xB8\x53\x22\x7E"
      "\x77\x29\x28\x31\x3A\x75\x36\x35\x3A\x00\xB3\xBB\x4D\xEE\x5A\xAF\xD0\xF2\x56\x8A"
      "\x10\x2D\x6F\x4B\x2D\x76\x49\x9B\xE9\xA8\x60\x5D\x9E\x7E\x50\x86\xF1\xA1\x0F\x28"
      "\x9B\x7B\xE8\xDD\x1F\x87\x4E\x79\x7B\x50\x12\xA7\xB4\x8B\x52\x38\xEC\x7C\xBB\xB9"
      "\x55\x87\x11\x1C\x74\xE7\x7F\xA0\xBA\xE3\x34\x5D\x61\xBF\x29\x29\x29\x00"
    };

  struct key_spec key_ecdsa_valid =
    {
      "\x28\x31\x31\x3A\x70\x72\x69\x76\x61\x74\x65\x2D\x6B\x65\x79\x28"
      "\x35\x3A\x65\x63\x64\x73\x61\x28\x35\x3A\x63\x75\x72\x76\x65\x31"
      "\x30\x3A\x4E\x49\x53\x54\x20\x50\x2D\x32\x35\x36\x29\x28\x31\x3A"
      "\x71\x36\x35\x3A\x04\x64\x5A\x12\x6F\x86\x7C\x43\x87\x2B\x7C\xAF"
      "\x77\xFE\xD8\x22\x31\xEA\xE6\x89\x9F\xAA\xEA\x63\x26\xBC\x49\xED"
      "\x85\xC6\xD2\xC9\x8B\x38\xD2\x78\x75\xE6\x1C\x27\x57\x01\xC5\xA1"
      "\xE3\xF9\x1F\xBE\xCF\xC1\x72\x73\xFE\xA4\x58\xB6\x6A\x92\x7D\x33"
      "\x1D\x02\xC9\xCB\x12\x29\x28\x31\x3A\x64\x33\x33\x3A\x00\x81\x2D"
      "\x69\x9A\x5F\x5B\x6F\x2C\x99\x61\x36\x15\x6B\x44\xD8\x06\xC1\x54"
      "\xC1\x4C\xFB\x70\x6A\xB6\x64\x81\x78\xF3\x94\x2F\x30\x5D\x29\x29"
      "\x28\x37\x3A\x63\x6F\x6D\x6D\x65\x6E\x74\x32\x32\x3A\x2F\x68\x6F"
      "\x6D\x65\x2F\x77\x6B\x2F\x2E\x73\x73\x68\x2F\x69\x64\x5F\x65\x63"
      "\x64\x73\x61\x29\x29"
    };


  struct
  {
    const char *key;
    const char *passphrase;
    int no_result_expected;
    int compare_results;
    unsigned char *result_expected;
    size_t resultlen_expected;
    int ret_expected;
    unsigned char *result;
    size_t resultlen;
  } specs[] =
    {
      /* Invalid S-Expressions  */
      /* - non-NULL  */
      { "",
	"passphrase", 1, 0, NULL, 0, GPG_ERR_INV_SEXP, NULL, 0 },
      /* - NULL; disabled, this segfaults  */
      //{ NULL,
      //  "passphrase", 1, NULL, 0, GPG_ERR_INV_SEXP, NULL, 0 },

      /* Valid and invalid keys.  */
      { key_rsa_valid.string,
	"passphrase", 0, 0, NULL, 0, 0, NULL, 0 },
      { key_rsa_bogus_0.string,
	"passphrase", 0, 0, NULL, 0, GPG_ERR_INV_SEXP, NULL, 0 },
      { key_rsa_bogus_1.string,
	"passphrase", 0, 0, NULL, 0, GPG_ERR_INV_SEXP, NULL, 0 },

      { key_ecdsa_valid.string,
	"passphrase", 0, 0, NULL, 0, 0, NULL, 0 },

      /* FIXME: add more test data.  */
    };

  for (i = 0; i < DIM (specs); i++)
    {
      ret = agent_protect ((const unsigned char*)specs[i].key,
                           specs[i].passphrase,
			   &specs[i].result, &specs[i].resultlen, 0, -1);
      if (gpg_err_code (ret) != specs[i].ret_expected)
	{
	  printf ("agent_protect(%d) returned '%i/%s'; expected '%i/%s'\n",
		  i, ret, gpg_strerror (ret),
		  specs[i].ret_expected, gpg_strerror (specs[i].ret_expected));
	  abort ();
	}

      if (specs[i].no_result_expected)
	{
	  assert (! specs[i].result);
	  assert (! specs[i].resultlen);
	}
      else
	{
	  if (specs[i].compare_results)
	    {
	      assert (specs[i].resultlen == specs[i].resultlen_expected);
	      if (specs[i].result_expected)
		assert (! memcmp (specs[i].result, specs[i].result_expected,
				  specs[i].resultlen));
	      else
		assert (! specs[i].result);
	    }
	  xfree (specs[i].result);
	}
    }
}


static void
test_agent_unprotect (void)
{
  /* Unprotect the key encoded in canonical format.  We assume a valid
     S-Exp here. */
/*   int  */
/*     agent_unprotect (const unsigned char *protectedkey, const char *passphrase, */
/*                      unsigned char **result, size_t *resultlen) */
}


static void
test_agent_private_key_type (void)
{
/* Check the type of the private key, this is one of the constants:
   PRIVATE_KEY_UNKNOWN if we can't figure out the type (this is the
   value 0), PRIVATE_KEY_CLEAR for an unprotected private key.
   PRIVATE_KEY_PROTECTED for an protected private key or
   PRIVATE_KEY_SHADOWED for a sub key where the secret parts are stored
   elsewhere. */
/* int */
/* agent_private_key_type (const unsigned char *privatekey) */
}


static void
test_make_shadow_info (void)
{
#if 0
  static struct
  {
    const char *snstr;
    const char *idstr;
    const char *expected;
  } data[] = {
    { "", "", NULL },

  };
  int i;
  unsigned char *result;

  for (i=0; i < DIM(data); i++)
    {
      result =  make_shadow_info (data[i].snstr, data[i].idstr);
      if (!result && !data[i].expected)
        pass ();
      else if (!result && data[i].expected)
        fail ();
      else if (!data[i].expected)
        fail ();
      /* fixme: Need to compare the result but also need to check
         proper S-expression syntax. */
    }
#endif
}



static void
test_agent_shadow_key (void)
{
/* Create a shadow key from a public key.  We use the shadow protocol
  "ti-v1" and insert the S-expressionn SHADOW_INFO.  The resulting
  S-expression is returned in an allocated buffer RESULT will point
  to. The input parameters are expected to be valid canonicalized
  S-expressions */
/* int  */
/* agent_shadow_key (const unsigned char *pubkey, */
/*                   const unsigned char *shadow_info, */
/*                   unsigned char **result) */
}


static void
test_agent_get_shadow_info (void)
{
/* Parse a canonical encoded shadowed key and return a pointer to the
   inner list with the shadow_info */
/* int  */
/* agent_get_shadow_info (const unsigned char *shadowkey, */
/*                        unsigned char const **shadow_info) */
}


static void
test_agent_protect_shared_secret (void)
{

}




int
main (int argc, char **argv)
{
  (void)argc;
  (void)argv;

  gcry_control (GCRYCTL_DISABLE_SECMEM);

  test_agent_protect ();
  test_agent_unprotect ();
  test_agent_private_key_type ();
  test_make_shadow_info ();
  test_agent_shadow_key ();
  test_agent_get_shadow_info ();
  test_agent_protect_shared_secret ();

  return 0;
}

/* Stub function.  */
gpg_error_t
convert_from_openpgp_native (gcry_sexp_t s_pgp, const char *passphrase,
                             unsigned char **r_key)
{
  (void)s_pgp;
  (void)passphrase;
  (void)r_key;
  return gpg_error (GPG_ERR_BUG);
}
