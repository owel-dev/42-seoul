import { PartialType } from '@nestjs/mapped-types';
import { CreateStatDto } from './create-stat.dto';
import { ApiProperty } from '@nestjs/swagger';

export class UpdateStatDto extends PartialType(CreateStatDto) { }
