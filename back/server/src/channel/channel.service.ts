import { Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { PostChannelDto } from './dto/post-channel.dto';
import { UpdateChannelDto } from './dto/update-channel.dto';
import { ChannelEntity } from './entities/channel.entity';

@Injectable()
export class ChannelService {
  constructor (
    @Inject('CHANNEL_REPOSITORY')
    private channelRepository: Repository<ChannelEntity>
  ){}

  async createChannel(postChannelDto: PostChannelDto) {
    const channel = new ChannelEntity();
    channel.player1 = postChannelDto.player1;
    channel.player2 = postChannelDto.player2;
    channel.admin = postChannelDto.admin;
    channel.curNumUser = 0;
    channel.maxNumUser = 10;
    channel.password = postChannelDto.password;
    channel.mode = postChannelDto.mode;
    channel.type = postChannelDto.type;

    await this.channelRepository.save(channel);
  }

  async getAllChannelList() {

    return await this.channelRepository.find();
  }

  async getOneChannel(id: number) {
    const result = await this.channelRepository.findOneBy({channelId : id});
    return result;
  }

  update(id: number, updateChannelDto: UpdateChannelDto) {
    return `This action updates a #${id} channel`;
  }

  remove(id: number) {
    return `This action removes a #${id} channel`;
  }
}
