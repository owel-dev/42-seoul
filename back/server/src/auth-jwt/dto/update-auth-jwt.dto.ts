import { PartialType } from '@nestjs/mapped-types';
import { CreateAuthJwtDto } from './create-auth-jwt.dto';

export class UpdateAuthJwtDto extends PartialType(CreateAuthJwtDto) {}
