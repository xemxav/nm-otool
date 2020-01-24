//
// Created by Xavier-emmanuel Moreau on 24/01/2020.
//

void		print_arch_struct(struct fat_arch arch)
{
	cpu_type_t	cputype;	/* cpu specifier (int) */
	cpu_subtype_t	cpusubtype;	/* machine specifier (int) */
	uint32_t	offset;		/* file offset to this object file */
	uint32_t	size;		/* size of this object file */
	uint32_t	align;

	swap(&cputype, &arch.cputype,sizeof(cpu_type_t));
	swap(&cpusubtype, &arch.cpusubtype,sizeof(cpu_type_t));
	swap(&offset, &arch.offset,sizeof(cpu_type_t));
	swap(&size, &arch.size,sizeof(cpu_type_t));
	swap(&align, &arch.align,sizeof(cpu_type_t));
	ft_printf("cputype =%d, cpusub=%d, offset=%x, size = %d, align = %d\n",
			  cputype, cpusubtype, offset, size, align);
}