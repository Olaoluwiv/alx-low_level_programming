#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);

/**
 * check_elf - Check if a file is an ELF file.
 * @e_ident: A pointer to an array containing the ELF magic.
 *
 * Description: If the file is not an ELF file, exit with code 98.
 */
void check_elf(unsigned char *e_ident)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 &&
			e_ident[index] != 'E' &&
			e_ident[index] != 'L' &&
			e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * print_magic - Print the magic number of an ELF.
 * @e_ident: A pointer containg an array of ELF magic.
 *
 * Description: Magic numbers are separated by spaces.
 */
void print_magic(unsigned char *e_ident)
{
	int index;

	printf("    magic:      ");
	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", e_ident[index]);
		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf("    ");
	}
}

/**
 * print_class - Print the class of an ELF header.
 * @e_ident: A pointer to an array containing ELF class.
 */
void print_class(unsigned char *e_ident)
{
	printf("  class: ");
	switch (e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * print_data - Print the data of an ELF header.
 * @e_ident: A pointer to an array containing ELF.
 */
void print_data(unsigned char *e_ident)
{
	printf("data:           ");
	switch (e_ident[EI_DATA])
	{
	case ELFDATANONE:
		printf("none\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_DATA]);
	}
}

/**
 * print_version - Print the version of an ELF.
 * @e_ident: A pointer to an array containing the ELF.
 */
void print_version(unsigned char *e_ident)
{
	printf("      version:       %d\n", e_ident[EI_VERSION]);
}

/**
 * print_osabi - Print the OS/ABI of the ELF.
 * @e_ident: A pointer to an array containing ELF.
 */
void print_osabi(unsigned char *e_ident)
{
	switch (e_ident[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf(" UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf(" UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone APP\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
 * print_type - Print the type of ELF header.
 * @e_type: The ELF type.
 * @e_ident: A pointer to an array containing ELF.
 */
void print_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;

	printf("   type:           ");
	switch (e_type)
	{
	case ET_NONE:
		printf("NONE (none)\n");
		break;
	case ET_REL:
		printf("REL (relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (core file)\n");
		break;
	default:
		printf("<unknown: %x>\n", e_type);
	}
}
