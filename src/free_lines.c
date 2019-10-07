/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:50:33 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/02 17:08:42 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void	free_lines(t_fdf *fdf)
{
	t_line	*cur;
	t_line	*tmp;

	cur = fdf->parser.lines;
	while (cur != NULL)
	{
		tmp = cur;
		free(cur->line);
		cur = cur->next;
		free(tmp);
	}
	fdf->parser.last_line = NULL;
	fdf->parser.lines = NULL;
}
