import { PartialType } from '@nestjs/mapped-types';
import { PostChannelDto } from './post-channel.dto';

export class UpdateChannelDto extends PartialType(PostChannelDto) {}
